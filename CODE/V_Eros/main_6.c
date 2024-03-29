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
#include "bvh.h"
#include "objets.h"

float time_scene = 0;
stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};


res_SDF (*My_scene_p)(vector); // pointeur vers la scene
res_SDF (*My_scene_bvh)(BVHNode*, vector); // pointeur vers la scene




int main(){
    clock_t begin_all = clock();


    srand(time(NULL));
    My_scene_p = SCENE_FIXE;

    BVHNode* MyBvhScene = scene1_bvh();
    My_scene_bvh = SCENE_BVH_Bis;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    window = glfwCreateWindow(WIDTH, HEIGHT, "Scene 1", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

    camera CAMERA;
    CAMERA.size_L_e = 2.0;
    CAMERA.dir_ecran_c = (vector){0,-1,0};

    CAMERA.up_c = normalise_vecteur((vector){0,0,1});
    CAMERA.position_c = (vector){25,50,25};
    CAMERA.dist_screen = 2.0;


    CAMERA.orthcam = normalise_vecteur(prod_vect(CAMERA.up_c, CAMERA.dir_ecran_c));
    CAMERA.de = CAMERA.size_L_e / WIDTH;
    CAMERA.size_l_e = HEIGHT*CAMERA.de;
    CAMERA.A = (vector){CAMERA.position_c.x + CAMERA.dist_screen*CAMERA.dir_ecran_c.x + CAMERA.size_l_e/2.0*CAMERA.up_c.x + CAMERA.size_L_e/2.0*CAMERA.orthcam.x,
               CAMERA.position_c.y + CAMERA.dist_screen*CAMERA.dir_ecran_c.y + CAMERA.size_l_e/2.0*CAMERA.up_c.y + CAMERA.size_L_e/2.0*CAMERA.orthcam.y,
               CAMERA.position_c.z + CAMERA.dist_screen*CAMERA.dir_ecran_c.z + CAMERA.size_l_e/2.0*CAMERA.up_c.z + CAMERA.size_L_e/2.0*CAMERA.orthcam.z};

    CAMERA.vlde = (vector){-CAMERA.de*CAMERA.up_c.x,
                           -CAMERA.de*CAMERA.up_c.y,
                           -CAMERA.de*CAMERA.up_c.z};

    CAMERA.vLde = (vector){-CAMERA.de*CAMERA.orthcam.x,
                           -CAMERA.de*CAMERA.orthcam.y,
                           -CAMERA.de*CAMERA.orthcam.z};


    // les directions dans lesquels doivent poartir les rayons 
    vector** ecran_ray_directions = malloc(WIDTH*sizeof(vector*));
    for (int i = 0; i < WIDTH; i++){
        ecran_ray_directions[i] = malloc(HEIGHT*sizeof(vector));
    }
    
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran_ray_directions[i][j] = normalise_vecteur(get_vec_2_pts(CAMERA.position_c,
                    (vector){CAMERA.A.x + i*CAMERA.vLde.x + j*CAMERA.vlde.x,
                            CAMERA.A.y + i*CAMERA.vLde.y + j*CAMERA.vlde.y,
                            CAMERA.A.z + i*CAMERA.vLde.z + j*CAMERA.vlde.z}));
        }
    }    

    /* Boucle principale */
    // while (!glfwWindowShouldClose(window)){
    for (int i = 0; i < 15; i++){
    
        glClear(GL_COLOR_BUFFER_BIT);

        time_scene += 1.0;

        // pour chaque pixel de l'ecran
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                // chaque rayon part de la camera en direction de chaque pixel (vect normaliser)
                ray R;
                R.origine = CAMERA.position_c;
                R.direction = ecran_ray_directions[i][j];
                color C = ray_marching_bvh_moving(R, MyBvhScene, My_scene_p, My_scene_bvh);
                draw_pixel(i, j, C, 1); // affiche le pixel                
            }
        }
        STATS.nb_images += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    clock_t end_all = clock();
    STATS.temps_tot = (double)(end_all-begin_all)/CLOCKS_PER_SEC;

    glfwTerminate();

    for (int i = 0; i < WIDTH; i++){
        free(ecran_ray_directions[i]);
    }
    free(ecran_ray_directions);

    return 0;
}

