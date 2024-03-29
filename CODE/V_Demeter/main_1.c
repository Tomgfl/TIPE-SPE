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

float time_scene = 0;
// stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};


RES_SDF (*My_scene_p)(VECTOR); // pointeur vers la scene


int main(){
    // clock_t begin_all = clock();

    

    srand(time(NULL));
    My_scene_p = scene_1;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    window = glfwCreateWindow(WIDTH, HEIGHT, "Main 1 - Tous les objets", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

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
    RAY** ecran_ray = malloc(WIDTH*sizeof(RAY*));
    for (int i = 0; i < WIDTH; i++){
        ecran_ray[i] = malloc(HEIGHT*sizeof(RAY));
    }

    COLOR** ecran_res = malloc(WIDTH*sizeof(COLOR*));
    for (int i = 0; i < WIDTH; i++){
        ecran_res[i] = malloc(HEIGHT*sizeof(COLOR));
    }
     
    
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran_ray[i][j].origine = cam.position_c;
            ecran_ray[i][j].direction = normalise_vecteur(get_vec_2_pts(cam.position_c,
                    (VECTOR){cam.A.x + i*cam.vLde.x + j*cam.vlde.x,
                            cam.A.y + i*cam.vLde.y + j*cam.vlde.y,
                            cam.A.z + i*cam.vLde.z + j*cam.vlde.z}));
        }
    }    

    // Preparation des threads
    pthread_t* threads = (pthread_t*) malloc(NB_THREADS*sizeof(pthread_t));
    ARG_THREAD* args = (ARG_THREAD*) malloc(NB_THREADS*sizeof(ARG_THREAD));


    for (int i = 0; i < NB_THREADS; i++){
        args[i] = (ARG_THREAD){My_scene_p,i,ecran_ray,ecran_res};
    }
    



    /* Boucle principale */
    // while (!glfwWindowShouldClose(window)){
    for (int img = 0; img < 10; img++){
    
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
            pthread_create(threads+i, NULL, ray_marching_thread, args+i);
        }
        for (int i = 0; i < NB_THREADS; i++){
            pthread_join(threads[i], NULL);
        }
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                draw_pixel(i,j,ecran_res[i][j],1);
            }
        }
        

        
        
        // STATS.nb_images += 1;
        // printf("ok\n");
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // clock_t end_all = clock();
    // STATS.temps_tot = (double)(end_all-begin_all)/CLOCKS_PER_SEC;

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
    // printf("Pourcentage temps pris par le calcul de la scene : %f\n", STATS.temps_tot/STATS.temps_scene *100);

    return 0;
}
