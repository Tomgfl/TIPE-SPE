#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "dessin_fct.h"
#include "options.h"
#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"
#include "light.h"
#include "scene.h"
#include "ray_marching.h"

float time_scene = 0;
STATS_OPTI Stats = {0,0,0,0,0,
0.0,0.0,0.0,0.0};


RES_SDF (*My_scene_p)(VECTOR); // pointeur vers la scene


int main(){

    srand(time(NULL));
    My_scene_p = scene_sphere;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit()){return -1;}
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Test 1", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    // --- V3 cam --- //
    // Pour toutes les scenes
    // CAMERA cam;
    // cam.size_L_e = 6.0;
    // cam.dir_ecran_c = (vector){0,1,0};

    // cam.up_c = normalise_vecteur((vector){0,0,1});
    // cam.position_c = (vector){0,-10,6};
    // cam.dist_screen = 3.0;

    CAMERA cam;
    cam.size_L_e = 2.0;
    cam.dir_ecran_c = (VECTOR){0,1,0};

    cam.up_c = normalise_vecteur((VECTOR){0,0,1});
    cam.position_c = (VECTOR){0,-20,5};
    cam.dist_screen = 2.0;


    cam.orthcam = normalise_vecteur(prod_vect(cam.up_c, cam.dir_ecran_c));
    cam.de = cam.size_L_e / WIDTH;
    cam.size_l_e = HEIGHT*cam.de;
    cam.A = (VECTOR){cam.position_c.x + cam.dist_screen*cam.dir_ecran_c.x + cam.size_l_e/2.0*cam.up_c.x + cam.size_L_e/2.0*cam.orthcam.x,
               cam.position_c.y + cam.dist_screen*cam.dir_ecran_c.y + cam.size_l_e/2.0*cam.up_c.y + cam.size_L_e/2.0*cam.orthcam.y,
               cam.position_c.z + cam.dist_screen*cam.dir_ecran_c.z + cam.size_l_e/2.0*cam.up_c.z + cam.size_L_e/2.0*cam.orthcam.z};

    cam.vlde = (VECTOR){-cam.de*cam.up_c.x,
                           -cam.de*cam.up_c.y,
                           -cam.de*cam.up_c.z};

    cam.vLde = (VECTOR){-cam.de*cam.orthcam.x,
                           -cam.de*cam.orthcam.y,
                           -cam.de*cam.orthcam.z};


    // les directions dans lesquels doivent poartir les rayons 
    VECTOR** ecran_ray_directions = malloc(WIDTH*sizeof(VECTOR*));
    for (int i = 0; i < WIDTH; i++){
        ecran_ray_directions[i] = malloc(HEIGHT*sizeof(VECTOR));
    }
    
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran_ray_directions[i][j] = normalise_vecteur(get_vec_2_pts(cam.position_c,
                    (VECTOR){cam.A.x + i*cam.vLde.x + j*cam.vlde.x,
                            cam.A.y + i*cam.vLde.y + j*cam.vlde.y,
                            cam.A.z + i*cam.vLde.z + j*cam.vlde.z}));
        }
    }
    

    
    
    

    /* Boucle principale */
    while (!glfwWindowShouldClose(window)){
    // for (int i = 0; i < 50; i++){
    
        glClear(GL_COLOR_BUFFER_BIT);


        
        time_scene += 10.0;

        // pour chaque pixel de l'ecran
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){

                // chaque rayon part de la cam en direction de chaque pixel (vect normaliser)
                RAY R;
                R.origine = cam.position_c;
                // comme dans ecran mais calcul direct ie calcule du vecteur de la cam vers chaque pixels
                //R.direction = normalise_vecteur(get_vec_2_pts(cam_c,(coord){p_cam->x - screen_mid_x + de*i, p_cam->y + screen_dist_y, p_cam->z + screen_mid_z - de*j}));
                // R.direction = normalise_vecteur(get_vec_2_pts(cam.position_c,
                //     (vector){cam.A.x + i*cam.vLde.x + j*cam.vlde.x,
                //             cam.A.y + i*cam.vLde.y + j*cam.vlde.y,
                //             cam.A.z + i*cam.vLde.z + j*cam.vlde.z}));
                R.direction = ecran_ray_directions[i][j];

                COLOR C = ray_marching(R, My_scene_p);
                draw_pixel(i, j, C, 1); // affiche le pixel                
            }
            printf("\033[H \n");
            printf("%.2f %%\n",(float)(i)/WIDTH*100.0);
            fflush(stdout);


            // glfwSwapBuffers(window);                                             //Répétition ?
            // glfwPollEvents();
        }
        // printf("ok\n");
        

        //printf("%f \n",SDF_triangle((vector){-8.0,-0.63,0.72},(vector){-9.0,0,0},(vector){-6,0,0},(vector){-8.3,-1.86,2.13}));
        //printf("%f \n",SDF_triangle((vector){-8.65,-1.3,1.7},(vector){-9.0,0,0},(vector){-6,0,0},(vector){-8.3,-1.86,2.13}));
        // cam.position_c.x -= 1;
        // cam.position_c.y += 1;
        // cam.position_c.z -= 1;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    

    glfwTerminate();
    return 0;
}
