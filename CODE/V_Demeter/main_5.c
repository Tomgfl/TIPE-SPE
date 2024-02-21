#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <pthread.h>

#include "dessin_fct.h"
#include "options.h"
#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"
#include "light.h"
#include "scene.h"
#include "ray_marching.h"
#include "nurbs.h"

float time_scene = 0;
STATS_OPTI Stats = {0,0,0,0,0,
0.0,0.0,0.0,0.0};


RES_SDF (*My_scene_p)(VECTOR); // pointeur vers la scene


int main(){
    clock_t begin_all = clock();

    srand(time(NULL));
    My_scene_p = nurbs_scene;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    window = glfwCreateWindow(WIDTH, HEIGHT, "Main 5 - Nurbs", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

    CAMERA cam;
    cam.size_L_e = 2.0;
    cam.dir_ecran_c = (VECTOR){1,0,0};

    cam.up_c = normalise_vecteur((VECTOR){0,0,1});
    cam.position_c = (VECTOR){-20,0,6};
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

    SURFACE nurbs_test = nurbs_2();
    affiche_surface(nurbs_test);

    // vector Q_1 = S_nurbs(0.0, 0.0, nurbs_test);
    // printf("Q_1 : %f | %f | %f \n", Q_1.x, Q_1.y, Q_1.z);

    // vector Q_2 = S_nurbs(0.99,0.0,nurbs_test);
    // printf("Q_2 : %f | %f | %f \n", Q_2.x, Q_2.y, Q_2.z);

    // vector Q_3 = S_nurbs(0.0,0.99,nurbs_test);
    // printf("Q_3 : %f | %f | %f \n", Q_3.x, Q_3.y, Q_3.z);

    // vector Q_4 = S_nurbs(0.99,0.99,nurbs_test);
    // printf("Q_4 : %f | %f | %f \n", Q_4.x, Q_4.y, Q_4.z);

    // vector Q = projection_nurbs(nurbs_test, (vector){1.0 ,-2.0, 3.0});
    // printf("Q : %f | %f | %f \n", Q.x, Q.y, Q.z);
    // return 0;




    // KNOTVECTOR U = create_knotvector(11);
    // U->U[0] = 0.0;
    // U->U[1] = 0.0;
    // U->U[2] = 0.0;
    // U->U[3] = 1.0;
    // U->U[4] = 2.0;
    // U->U[5] = 3.0;
    // U->U[6] = 4.0;
    // U->U[7] = 4.0;
    // U->U[8] = 5.0;
    // U->U[9] = 5.0;
    // U->U[10] = 5.0;

    /* OK
    printf("N_00(-7.4) :%.2f (0)\n", N_base_fct(0,0,-7.4,U));
    printf("N_00(0) :%.2f (0)\n", N_base_fct(0,0,0.0,U));
    printf("N_10(6) :%.2f (0)\n", N_base_fct(1,0,6.0,U));
    printf("N_10(0.5) :%.2f (0)\n", N_base_fct(1,0,0,U));
    printf("\n");

    printf("N_20(0.5) :%.2f (1)\n", N_base_fct(2,0,0.5,U));
    printf("N_20(0) :%.2f (1)\n", N_base_fct(2,0,0.0,U));
    printf("N_20(1) :%.2f (0)\n", N_base_fct(2,0,1.0,U));
    printf("\n");

    printf("N_70(4.5) :%.2f (1)\n", N_base_fct(7,0,4.5,U));
    printf("N_70(3.9) :%.2f (0)\n", N_base_fct(7,0,3.9,U));
    printf("N_70(4) :%.2f (1)\n", N_base_fct(7,0,4.0,U));
    printf("N_70(5) :%.2f (0)\n", N_base_fct(7,0,5.0,U));
    printf("\n");
    */

    // printf("N_11(0) :%.2f (1)\n", N_base_fct(1,1,0.0,U));
    // printf("N_11(0.5) :%f (0.5)\n", N_base_fct(1,1,0.5,U));
    // printf("N_11(1) :%.2f (0)\n", N_base_fct(1,1,1.0,U));
    // printf("N_11(1.5) :%.2f (0)\n", N_base_fct(1,1,1.5,U));
    // printf("\n");

    // printf("N_42(2) :%f (0)\n", N_base_fct(4,2,2.0,U));
    // printf("N_42(2.5) :%f (0.125)\n", N_base_fct(4,2,2.5,U));
    // printf("N_42(3) :%f (0.5)\n", N_base_fct(4,2,3.0,U));
    // printf("N_42(3.5) :%f (0.625)\n", N_base_fct(4,2,3.5,U));
    // printf("N_42(4) :%f (0)\n", N_base_fct(4,2,4.0,U));


    
    // Boucle principale 
    while (!glfwWindowShouldClose(window)){
    // for (int i = 0; i < 50; i++){
    
        glClear(GL_COLOR_BUFFER_BIT);

        time_scene += 1.0;

        // // pour chaque pixel de l'ecran
        // for (int i = 0; i < WIDTH; i++){
        //     for (int j = 0; j < HEIGHT; j++){
        //         // chaque rayon part de la cam en direction de chaque pixel (vect normaliser)
        //         ray R;
        //         R.origine = cam.position_c;
        //         R.direction = ecran_ray_directions[i][j];
        //         color C = ray_marching(R, My_scene_p);
        //         draw_pixel(i, j, C, 1); // affiche le pixel  
        //         glfwSwapBuffers(window);
        //         glfwPollEvents();              
        //     }
        //     printf("\033[H \n");
        //     printf("%.2f %%\n",(float)(i)/WIDTH*100.0);
        //     fflush(stdout);
        //     glfwSwapBuffers(window);
        //     glfwPollEvents();
        // }
        // // printf("ok\n");
        // Stats.nb_images += 1;
        // glfwSwapBuffers(window);
        // glfwPollEvents();
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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    /*
    clock_t end_all = clock();
    Stats.temps_tot = (double)(end_all-begin_all)/CLOCKS_PER_SEC;

    glfwTerminate();

    for (int i = 0; i < WIDTH; i++){
        free(ecran_ray_directions[i]);
    }
    free(ecran_ray_directions);

    printf("Nombre d'image rendu : %d\n", Stats.nb_images);
    printf("Temps d'execution total : %f sec\n", Stats.temps_tot);
    printf("FPS : %f\n", Stats.nb_images / Stats.temps_tot);
    printf("Temps moyen d'une image : %f sec\n", Stats.temps_tot / Stats.nb_images);
    printf("Temps calcul lumière : %f sec\n", Stats.temps_light);
    printf("Temps calcul ombres : %f sec\n", Stats.temps_shadow);
    printf("Temps calcul ray_marching seul : %f sec\n", Stats.temps_raymarch);
    // printf("Temps pris pour le calcul du min d'une scene (compris dans ray et ombre) : %f sec\n", Stats.temps_scene);
    printf("Nombre total de rayons lancé pour le ray-marching : %lld\n",Stats.nb_rayons_tot);
    printf("Nombre total d'étapes pour les rayons du ray-marching : %lld\n", Stats.nb_rayons_etapes);
    printf("Nombre moyen d'étapes ray-marching : %.2f\n", (double)Stats.nb_rayons_etapes / Stats.nb_rayons_tot);
    printf("Nombre total de rayon lancé pour les ombres : %lld\n", Stats.nb_shadow_rayons_tot);
    printf("Nombre total d'étapes pour les ombres : %lld\n", Stats.nb_shadow_rayons_etapes);
    printf("Nombre moyen d'étapes ombres : %.2f\n", (double)Stats.nb_shadow_rayons_etapes / Stats.nb_shadow_rayons_tot);
    printf("Poucentage temps pris pour ray-march | lumière | ombre | autre : %.2f | %.2f | %.2f | %.2f\n",
        Stats.temps_raymarch/Stats.temps_tot*100, Stats.temps_light/Stats.temps_tot*100, Stats.temps_shadow/Stats.temps_tot*100, (Stats.temps_tot - Stats.temps_light - Stats.temps_shadow - Stats.temps_raymarch)/Stats.temps_tot*100);
    printf("\n");

    */

    return 0;
}





































// struct param_sphere_s{
//     float rayon;
//     vector centre;
//     color couleur;
// };
// typedef struct param_sphere_s param_sphrere;



// res_SDF SDF_sphere(vector p, void* param){
//     param_sphrere* args = (param_sphrere*) param; // Pour dire a la fonction que on 
//                                                   // utilise des parametre de boule

//     float d = sqrt((p.x - args->centre.x)*(p.x - args->centre.x) + 
//                    (p.y - args->centre.y)*(p.y - args->centre.y) +
//                    (p.z - args->centre.z)*(p.z - args->centre.z));

//     res_SDF res;
//     res.dist = d - args->rayon;
//     res.c = args->couleur;
//     return res;
// }

