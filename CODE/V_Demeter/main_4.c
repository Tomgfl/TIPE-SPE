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
    clock_t begin_all = clock();

    srand(time(NULL));
    My_scene_p = scene_1;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    window = glfwCreateWindow(WIDTH, HEIGHT, "Main 4 - Paysage", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

    CAMERA cam;
    cam.size_L_e = 2.0;
    cam.dir_ecran_c = (VECTOR){1,0,0};

    cam.up_c = normalise_vecteur((VECTOR){0,0,1});
    cam.position_c = (VECTOR){-10,0,0};
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

        time_scene += 1.0;

        // pour chaque pixel de l'ecran
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                // chaque rayon part de la cam en direction de chaque pixel (vect normaliser)
                RAY R;
                R.origine = cam.position_c;
                R.direction = ecran_ray_directions[i][j];
                COLOR C = ray_marching(R, My_scene_p);
                draw_pixel(i, j, C, 1); // affiche le pixel                
            }
            // printf("\033[H \n");
            // printf("%.2f %%\n",(float)(i)/WIDTH*100.0);
            // fflush(stdout);
            // glfwSwapBuffers(window);                                             //Répétition ?
            // glfwPollEvents();
        }
        // printf("ok\n");
        Stats.nb_images += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
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

    return 0;
}
