#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>


#include "dessin_fct.h"
#include "options.h"
#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"
#include "light.h"
#include "scene.h"
#include "pingouin_sdf.h"
#include "simpsons_bvh.h"
#include "plage_bvh.h"
#include "ray_marching.h"
#include "bvh.h"
#include "objets.h"

float time_scene = 0;
stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};


res_SDF (*My_scene_p)(vector); // pointeur vers la scene
res_SDF (*My_scene_bvh_fix)(BVHNode*, vector, res_SDF); // pointeur vers la scene
res_SDF (*My_scene_bvh_move)(BVHNode*, vector); // pointeur vers la scene




int main(){
    // clock_t begin_all = clock();

    vector n_plan = {0, 0, -1000000}; vector m_plan = {0, 0, -1000000}; color c_plan  = c_blanc;

    srand(time(NULL));
    My_scene_p = scene_banquise;

    BVHNode* MyBvhScene = TestBanquise();
    My_scene_bvh_move = SCENE_BVH_Bis;
    My_scene_bvh_fix = SCENE_BVH;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    window = glfwCreateWindow(WIDTH, HEIGHT, "Scene 1", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

    camera CAMERA;
    CAMERA.size_L_e = 2.0;
    CAMERA.dir_ecran_c = (vector){1,-0.6,-1};

    CAMERA.up_c = normalise_vecteur((vector){0,1,0});
    CAMERA.position_c = (vector){-20,15,20};
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
    ray** ecran_ray = malloc(WIDTH*sizeof(ray*));
    for (int i = 0; i < WIDTH; i++){
        ecran_ray[i] = malloc(HEIGHT*sizeof(ray));
    }

    color** ecran_res = malloc(WIDTH*sizeof(color*));
    for (int i = 0; i < WIDTH; i++){
        ecran_res[i] = malloc(HEIGHT*sizeof(color));
    }
    
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran_ray[i][j].origine = CAMERA.position_c;
            ecran_ray[i][j].direction = normalise_vecteur(get_vec_2_pts(CAMERA.position_c,
                    (vector){CAMERA.A.x + i*CAMERA.vLde.x + j*CAMERA.vlde.x,
                            CAMERA.A.y + i*CAMERA.vLde.y + j*CAMERA.vlde.y,
                            CAMERA.A.z + i*CAMERA.vLde.z + j*CAMERA.vlde.z}));
        }
    }      


    // Preparation des threads
    pthread_t* threads = (pthread_t*) malloc(NB_THREADS*sizeof(pthread_t));
    arg* args = (arg*) malloc(NB_THREADS*sizeof(arg));


    for (int i = 0; i < NB_THREADS; i++){
        args[i] = (arg){My_scene_p, My_scene_bvh_fix, My_scene_bvh_move,MyBvhScene,i,ecran_ray,ecran_res,n_plan,m_plan,c_plan};
    }


    /* Boucle principale */
    // while (!glfwWindowShouldClose(window)){
    for (int img = 0; img < 5; img++){
    
        glClear(GL_COLOR_BUFFER_BIT);

        time_scene += 1.0;

        for (int i = 0; i < NB_THREADS; i++){
            pthread_create(threads+i, NULL, ray_marching_bvh_thread, args+i);
        }
        for (int i = 0; i < NB_THREADS; i++){
            pthread_join(threads[i], NULL);
        }
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                draw_pixel(i,j,ecran_res[i][j],1);
            }
        }

        STATS.nb_images += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    for (int i = 0; i < WIDTH; i++){
        free(ecran_ray[i]);
        free(ecran_res[i]);
    }
    free(ecran_ray);
    free(ecran_res);
    free(args);
    free(threads);
}
