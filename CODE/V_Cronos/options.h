#ifndef OPTION_H 
#define OPTION_H

// structs
// vecteur 3d
struct vector_s{
    float x, y, z;
};
typedef struct vector_s vector;

// --- COULEURS --- //
struct color_s{
    int r, g, b;
    float opp; // oppaciter de la couleur 
};
typedef struct color_s color;

// rayon
struct ray_s{
    vector origine;
    vector direction;
};
typedef struct ray_s ray;

// Tout ce qui concerne la camera et l'ecran
struct camera_s{
    vector position_c;  // Position de la camera
    vector dir_ecran_c; // Direction de la camera
    vector up_c;        // Vecteur representent le haut de la camera

    float size_L_e;     // Longueur de l'ecran
    float dist_screen;  // Distance de la camera a l'ecran

    float size_l_e;     // Largeur de l'ecran (a calculer)
    vector orthcam;     // vecteur orthogonal a up et dir (a calculer)
    float de;           // Taille d'un pixel de l'ecran (a calculer)
    vector vLde;        // Vecteur AB de taille de (a calculer)
    vector vlde;        // Vecteur AD de taille de (a calculer)
    vector A;           // Coin haut gauche de l'ecran (a calculer)
};
typedef struct camera_s camera;

// https://timcoster.com/2020/03/05/raymarching-shader-pt5-colors/
struct res_SDF_s{
    float dist;
    color c;
    vector centre;
    float rayon;    // Distance la plus grande
}; 
typedef struct res_SDF_s res_SDF;

// structure pour le resultat d'un systeme 2 2 
struct res_systeme_2_s{
    float det;
    float x;
    float y; 
};
typedef struct res_systeme_2_s res_systeme_2;

struct stats_opti_s{
    // pour le raymarching principal
    long long int nb_rayons_tot;            // fait
    long long int nb_rayons_etapes;         // fait

    // pour le calcule des ombres
    long long int nb_shadow_rayons_tot;     // fait
    long long int nb_shadow_rayons_etapes;  // fait
    
    int nb_images;                          // fait m

    double temps_tot;                       // fait m
    double temps_raymarch;                  // fait
    double temps_light;                     // fait
    double temps_shadow;                    // fait                   

};
typedef struct stats_opti_s stats_opti;


// Pour pthread
struct arg_s{
    res_SDF (*fct_scene)(vector);
    int id;             // id du thread
    ray** t_in;         // les rayons de l'ecran
    color** t_out;      // tab du resultat
};
typedef struct arg_s arg;


// taille de l'ecran
#define WIDTH 600
#define HEIGHT 480

// Parametres du ray marching
#define MAX_RAY_STEPS 512 // nombre max d'étape
#define DIST_MIN 0.01 // diatance a partir de laquel on a atteint un objet
#define MAX_TOTAL_LENGHT 500 // distance max que peut parcourir un rayon
#define EPSILON 0.00001 // pour le calcule des gradients

#define NB_THREADS 12



#endif 