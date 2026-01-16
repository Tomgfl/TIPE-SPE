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

// Variables globales nécessaires
float time_scene = 0;
stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};

// Pointeurs de fonctions pour la scène
res_SDF (*My_scene_p)(vector); 
res_SDF (*My_scene_bvh_fix)(BVHNode*, vector, res_SDF); 
res_SDF (*My_scene_bvh_move)(BVHNode*, vector); 

// --- CRÉATION DE LA SCÈNE SIMPLE --- //

// 1. Fonction qui construit le BVH (Arbre des objets)
BVHNode* Build_Simple_Scene_BVH() {
    int nb = 3;
    OBJET* all_obj = malloc(nb * sizeof(OBJET));

    // Objet 1 : Un sol (Boite plate grise)
    // BuildBox(Centre, Longueur, Largeur, Hauteur, Couleur)
    all_obj[0] = BuildBox((vector){0, -2, 0}, 10, 0.5, 10, c_gris);

    // Objet 2 : Une Sphère Rouge au centre
    // BuildSphere(Centre, Rayon, Couleur)
    all_obj[1] = BuildSphere((vector){0, 1, 0}, 1.5, c_rouge);

    // Objet 3 : Un Tore Bleu autour de la sphère
    // BuildTor(Centre, GrandRayon, PetitRayon, Couleur)
    all_obj[2] = BuildTor((vector){0, 1, 0}, 2.5, 0.3, c_bleu);

    

    // Construction de l'arbre BVH
    BVHNode* root = buildBVH(all_obj, nb);
    return root;
}

// 2. Wrapper SDF (nécessaire pour la compatibilité avec certaines fonctions de lumière)
// Cette fonction recrée le BVH à la volée pour un test ponctuel (moins performant mais sûr)
res_SDF Simple_Scene_Wrapper(vector pts) {
    res_SDF maxsdf = (res_SDF){FLT_MAX, c_blanc};
    BVHNode* temp_bvh = Build_Simple_Scene_BVH();
    res_SDF res = traverseBVH(temp_bvh, pts, maxsdf);
    freeBVH(temp_bvh); // Important : on libère pour éviter les fuites de mémoire
    return res;
}

// --- MAIN --- //

int main(){
    vector n_plan = {0, 0, -1000000}; 
    vector m_plan = {0, 0, -1000000}; 
    color c_plan  = c_blanc;

    srand(time(NULL));

    // Initialisation des pointeurs de scène
    My_scene_p = Simple_Scene_Wrapper;
    
    // On construit la scène une seule fois pour le RayMarching principal
    BVHNode* MyBvhScene = Build_Simple_Scene_BVH();
    
    // Assignation des fonctions de traversée (existantes dans ton projet)
    My_scene_bvh_move = SCENE_BVH_Bis;
    My_scene_bvh_fix = SCENE_BVH;

    // --- GESTION DE LA FENETRE --- //
    GLFWwindow* window;
    if (!glfwInit()){return -1;}
    
    // Création fenêtre
    window = glfwCreateWindow(WIDTH, HEIGHT, "Test Scene Simple", NULL, NULL);
    if (!window){glfwTerminate();return -1;}
    glfwMakeContextCurrent(window);

    // --- CAMERA (Positionnée pour voir la scène (0,0,0) de haut et de biais) --- //
    camera CAMERA;
    CAMERA.size_L_e = 2.0;
    
    // Position de la caméra (x, y, z)
    CAMERA.position_c = (vector){5, 4, 5}; 

    // Direction : On regarde vers l'origine (0,0,0)
    // Vecteur = Destination(0,0,0) - Origine(5,4,5) = (-5, -4, -5)
    CAMERA.dir_ecran_c = normalise_vecteur((vector){-5, -4, -5});
    CAMERA.up_c = normalise_vecteur((vector){0,1,0});
    CAMERA.dist_screen = 2.0;

    // Calculs vecteurs caméra (inchangés)
    CAMERA.orthcam = normalise_vecteur(prod_vect(CAMERA.up_c, CAMERA.dir_ecran_c));
    CAMERA.de = CAMERA.size_L_e / WIDTH;
    CAMERA.size_l_e = HEIGHT*CAMERA.de;
    CAMERA.A = (vector){
        CAMERA.position_c.x + CAMERA.dist_screen*CAMERA.dir_ecran_c.x + CAMERA.size_l_e/2.0*CAMERA.up_c.x + CAMERA.size_L_e/2.0*CAMERA.orthcam.x,
        CAMERA.position_c.y + CAMERA.dist_screen*CAMERA.dir_ecran_c.y + CAMERA.size_l_e/2.0*CAMERA.up_c.y + CAMERA.size_L_e/2.0*CAMERA.orthcam.y,
        CAMERA.position_c.z + CAMERA.dist_screen*CAMERA.dir_ecran_c.z + CAMERA.size_l_e/2.0*CAMERA.up_c.z + CAMERA.size_L_e/2.0*CAMERA.orthcam.z
    };

    CAMERA.vlde = (vector){-CAMERA.de*CAMERA.up_c.x, -CAMERA.de*CAMERA.up_c.y, -CAMERA.de*CAMERA.up_c.z};
    CAMERA.vLde = (vector){-CAMERA.de*CAMERA.orthcam.x, -CAMERA.de*CAMERA.orthcam.y, -CAMERA.de*CAMERA.orthcam.z};

    // Allocation Rayons
    ray** ecran_ray = malloc(WIDTH*sizeof(ray*));
    color** ecran_res = malloc(WIDTH*sizeof(color*));
    for (int i = 0; i < WIDTH; i++){
        ecran_ray[i] = malloc(HEIGHT*sizeof(ray));
        ecran_res[i] = malloc(HEIGHT*sizeof(color));
    }
    
    // Initialisation Rayons
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran_ray[i][j].origine = CAMERA.position_c;
            ecran_ray[i][j].direction = normalise_vecteur(get_vec_2_pts(CAMERA.position_c,
                    (vector){CAMERA.A.x + i*CAMERA.vLde.x + j*CAMERA.vlde.x,
                            CAMERA.A.y + i*CAMERA.vLde.y + j*CAMERA.vlde.y,
                            CAMERA.A.z + i*CAMERA.vLde.z + j*CAMERA.vlde.z}));
        }
    }      

    // Preparation Threads
    pthread_t* threads = (pthread_t*) malloc(NB_THREADS*sizeof(pthread_t));
    arg* args = (arg*) malloc(NB_THREADS*sizeof(arg));

    for (int i = 0; i < NB_THREADS; i++){
        args[i] = (arg){My_scene_p, My_scene_bvh_fix, My_scene_bvh_move, MyBvhScene, i, ecran_ray, ecran_res, n_plan, m_plan, c_plan};
    }

    // --- BOUCLE PRINCIPALE --- //
    // J'ai mis une boucle infinie tant que la fenêtre est ouverte
    while (!glfwWindowShouldClose(window)){
    
        glClear(GL_COLOR_BUFFER_BIT);

        // On n'incrémente plus time_scene pour garder les objets fixes si des shaders l'utilisent
        // time_scene += 1.0; 

        // Lancement Threads
        for (int i = 0; i < NB_THREADS; i++){
            pthread_create(threads+i, NULL, ray_marching_bvh_thread, args+i);
        }
        // Attente Threads
        for (int i = 0; i < NB_THREADS; i++){
            pthread_join(threads[i], NULL);
        }
        // Dessin
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                draw_pixel(i,j,ecran_res[i][j],1);
            }
        }

        STATS.nb_images += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Nettoyage
    glfwTerminate();

    for (int i = 0; i < WIDTH; i++){
        free(ecran_ray[i]);
        free(ecran_res[i]);
    }
    free(ecran_ray);
    free(ecran_res);
    free(args);
    free(threads);
    // freeBVH(MyBvhScene); // Idéalement, il faudrait une fonction pour libérer le BVH principal à la fin
    
    return 0;
}