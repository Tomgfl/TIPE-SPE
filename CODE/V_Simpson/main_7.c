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
#include "ray_marching.h"
#include "bvh.h"
#include "objets.h"

float time_scene = 0;
stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};


res_SDF (*My_scene_p)(vector); // pointeur vers la scene
res_SDF (*My_scene_bvh_fix)(BVHNode*, vector, res_SDF); // pointeur vers la scene
res_SDF (*My_scene_bvh_move)(BVHNode*, vector); // pointeur vers la scene


int main(){
    clock_t begin_all = clock();

    srand(time(NULL));
    My_scene_p = SCENE_FIXE;

    BVHNode* MyBvhScene = scene1_bvh();
    My_scene_bvh_move = SCENE_BVH_Bis;

    vector n_plan = {0, 0, 1}; vector m_plan = {0, 0, -4}; color c_plan = c_gris;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    window = glfwCreateWindow(WIDTH, HEIGHT, "Scene 1", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

    camera CAMERA;
    CAMERA.size_L_e = 2.0;
    CAMERA.dir_ecran_c = (vector){1,0,0};

    CAMERA.up_c = normalise_vecteur((vector){0,0,1});
    CAMERA.position_c = (vector){0,0,0};
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
    for (int img = 0; img < 20; img++){
    
        glClear(GL_COLOR_BUFFER_BIT);

        time_scene += 1.0;


        // pour chaque pixel de l'ecran
        // for (int i = 0; i < WIDTH; i++){
        //     for (int j = 0; j < HEIGHT; j++){
        //         // chaque rayon part de la camera en direction de chaque pixel (vect normaliser)
        //         ray R;
        //         R.origine = CAMERA.position_c;
        //         R.direction = ecran_ray_directions[i][j];
        //         // clock_t begin_r = clock();
        //         color C = ray_marching(R, My_scene_p);
        //         // clock_t end_r = clock();
        //         // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
        //         draw_pixel(i, j, C, 1); // affiche le pixel                
        //     }
        // }
        for (int i = 0; i < NB_THREADS; i++){
            pthread_create(threads+i, NULL, ray_marching_bvh_thread_move, args+i);
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
        // printf("ok\n");
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    clock_t end_all = clock();
    STATS.temps_tot = (double)(end_all-begin_all)/CLOCKS_PER_SEC;

    glfwTerminate();

    for (int i = 0; i < WIDTH; i++){
        free(ecran_ray[i]);
        free(ecran_res[i]);
    }
    free(ecran_ray);
    free(ecran_res);
    free(args);
    free(threads);

    // printf("Nombre d'image rendu : %d\n", STATS.nb_images);
    // printf("Temps d'execution total : %f sec\n", STATS.temps_tot);
    // printf("FPS : %f\n", STATS.nb_images / STATS.temps_tot);
    // printf("Temps moyen d'une image : %f sec\n", STATS.temps_tot / STATS.nb_images);
    // printf("Temps calcul lumière : %f sec\n", STATS.temps_light);
    // printf("Temps calcul ombres : %f sec\n", STATS.temps_shadow);
    // printf("Temps calcul ray_marching seul : %f sec\n", STATS.temps_raymarch);
    // // printf("Temps pris pour le calcul du min d'une scene (compris dans ray et ombre) : %f sec\n", STATS.temps_scene);
    // printf("Nombre total de rayons lancé pour le ray-marching : %lld\n",STATS.nb_rayons_tot);
    // printf("Nombre total d'étapes pour les rayons du ray-marching : %lld\n", STATS.nb_rayons_etapes);
    // printf("Nombre moyen d'étapes ray-marching : %.2f\n", (double)STATS.nb_rayons_etapes / STATS.nb_rayons_tot);
    // printf("Nombre total de rayon lancé pour les ombres : %lld\n", STATS.nb_shadow_rayons_tot);
    // printf("Nombre total d'étapes pour les ombres : %lld\n", STATS.nb_shadow_rayons_etapes);
    // printf("Nombre moyen d'étapes ombres : %.2f\n", (double)STATS.nb_shadow_rayons_etapes / STATS.nb_shadow_rayons_tot);
    // printf("Poucentage temps pris pour ray-march | lumière | ombre | autre : %.2f | %.2f | %.2f | %.2f\n",
    //     STATS.temps_raymarch/STATS.temps_tot*100, STATS.temps_light/STATS.temps_tot*100, STATS.temps_shadow/STATS.temps_tot*100, (STATS.temps_tot - STATS.temps_light - STATS.temps_shadow - STATS.temps_raymarch)/STATS.temps_tot*100);
    // printf("\n");

    return 0;
}