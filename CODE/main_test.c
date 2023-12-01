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


color c_rouge = {255,0,0,1.0};
color c_bleu = {0,0,255,1.0};
color c_vert = {0,255,0,1.0};
color c_noir = {0,0,0,1.0};
color c_blanc = {255,255,255,1.0};
color c_gris = {63, 63, 63,1.0};
color c_fond = {3,27,73,1.0};



// renvoie la couleur d'un rayon avec le ray marching
color ray_marching(ray r){
    float dist_tot = 0.0;
    coord position_actuelle = r.origine;

    coord Lumiere = {4.0, 5.0, 30.0}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = MIN_ALL_SDF(position_actuelle);
        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet

            float val_light = all_light(position_actuelle, Lumiere);

            float val_shadow = shadow_1(position_actuelle, Lumiere);

            color res = {150.0, 150.0, 15.0, val_light*val_shadow};
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    return c_rouge;
}




int main(){
    srand(time(NULL));
    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit()){return -1;}
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Test 1", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    // --- V3 CAMERA --- //
    camera CAMERA;
    CAMERA.size_L_e = 6.0;
    CAMERA.dir_ecran_c = (vector){0,1,0};

    CAMERA.up_c = normalise_vecteur((vector){0,0,1});
    CAMERA.position_c = (coord){0,-10,6};
    CAMERA.dist_screen = 3.0;

    CAMERA.orthcam = normalise_vecteur(prod_vect(CAMERA.up_c, CAMERA.dir_ecran_c));
    CAMERA.de = CAMERA.size_L_e / WIDTH;
    CAMERA.size_l_e = HEIGHT*CAMERA.de;
    CAMERA.A = (coord){CAMERA.position_c.x + CAMERA.dist_screen*CAMERA.dir_ecran_c.x + CAMERA.size_l_e/2.0*CAMERA.up_c.x + CAMERA.size_L_e/2.0*CAMERA.orthcam.x,
               CAMERA.position_c.y + CAMERA.dist_screen*CAMERA.dir_ecran_c.y + CAMERA.size_l_e/2.0*CAMERA.up_c.y + CAMERA.size_L_e/2.0*CAMERA.orthcam.y,
               CAMERA.position_c.z + CAMERA.dist_screen*CAMERA.dir_ecran_c.z + CAMERA.size_l_e/2.0*CAMERA.up_c.z + CAMERA.size_L_e/2.0*CAMERA.orthcam.z};

    CAMERA.vlde = (vector){-CAMERA.de*CAMERA.up_c.x,
                           -CAMERA.de*CAMERA.up_c.y,
                           -CAMERA.de*CAMERA.up_c.z};

    CAMERA.vLde = (vector){-CAMERA.de*CAMERA.orthcam.x,
                           -CAMERA.de*CAMERA.orthcam.y,
                           -CAMERA.de*CAMERA.orthcam.z};


    

    /* Boucle principale */
    while (!glfwWindowShouldClose(window)){
    // for (int i = 0; i < 50; i++){
    
        glClear(GL_COLOR_BUFFER_BIT);


        // color ecran_color[WIDTH][HEIGHT];

        // pour chaque pixel de l'ecran
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){

                // chaque rayon part de la camera en direction de chaque pixel (vect normaliser)
                ray R;
                R.origine = CAMERA.position_c;
                // comme dans ecran mais calcul direct ie calcule du vecteur de la cam vers chaque pixels
                //R.direction = normalise_vecteur(get_vec_2_pts(cam_c,(coord){p_cam->x - screen_mid_x + de*i, p_cam->y + screen_dist_y, p_cam->z + screen_mid_z - de*j}));
                R.direction = normalise_vecteur(get_vec_2_pts(CAMERA.position_c,
                    (coord){CAMERA.A.x + i*CAMERA.vLde.x + j*CAMERA.vlde.x,
                            CAMERA.A.y + i*CAMERA.vLde.y + j*CAMERA.vlde.y,
                            CAMERA.A.z + i*CAMERA.vLde.z + j*CAMERA.vlde.z}));

                color C = ray_marching(R);
                draw_pixel(i, j, C, 1); // affiche le pixel
            }
        }
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
