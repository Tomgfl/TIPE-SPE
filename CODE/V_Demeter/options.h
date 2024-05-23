#ifndef OPTION_H 
#define OPTION_H

// structs
// vecteur 3d
struct vector_s{
    float x, y, z;
};
typedef struct vector_s VECTOR;

// --- COULEURS --- //
struct color_s{
    int r, g, b;
    float opp; // oppaciter de la couleur 
};
typedef struct color_s COLOR;

// rayon
struct ray_s{
    VECTOR origine;
    VECTOR direction;
};
typedef struct ray_s RAY;

// Tout ce qui concerne la camera et l'ecran
struct camera_s{
    VECTOR position_c;  // Position de la camera
    VECTOR dir_ecran_c; // Direction de la camera
    VECTOR up_c;        // Vecteur representent le haut de la camera

    float size_L_e;     // Longueur de l'ecran
    float dist_screen;  // Distance de la camera a l'ecran

    float size_l_e;     // Largeur de l'ecran (a calculer)
    VECTOR orthcam;     // vecteur orthogonal a up et dir (a calculer)
    float de;           // Taille d'un pixel de l'ecran (a calculer)
    VECTOR vLde;        // Vecteur AB de taille de (a calculer)
    VECTOR vlde;        // Vecteur AD de taille de (a calculer)
    VECTOR A;           // Coin haut gauche de l'ecran (a calculer)
};
typedef struct camera_s CAMERA;

// https://timcoster.com/2020/03/05/raymarching-shader-pt5-colors/
struct res_SDF_s{
    float dist;
    COLOR c;
}; 
typedef struct res_SDF_s RES_SDF;

// structure pour le resultat d'un systeme 2 2 
struct res_systeme_2_s{
    float det;
    float x;
    float y; 
};
typedef struct res_systeme_2_s RES_SYS_2;

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
typedef struct stats_opti_s STATS_OPTI;

struct stats_nurbs_s{
    long int nb_iterations;
    long int nb_points;
};
typedef struct stats_nurbs_s* STATS_NURBS;

// Pour pthread
struct arg_thread_s{
    RES_SDF (*fct_scene)(VECTOR);
    int id;             // id du thread
    RAY** t_in;         // les rayons de l'ecran
    COLOR** t_out;      // tab du resultat
};
typedef struct arg_thread_s ARG_THREAD;


// Pour les nurbs
// Point de controle
struct cpoint_s{
    float x, y, z, w;
};
typedef struct cpoint_s CPOINT;

// Controle net
struct cnet_s{
    int n;
    int m;
    CPOINT** Pw;
};
typedef struct cnet_s* CNET;

// Vecteur nodal
struct knotvector_s{
    int m;
    float* U;
};
typedef struct knotvector_s* KNOTVECTOR;

// nurbs surface
struct surface_s{
    CNET net;
    int p;
    int q;
    KNOTVECTOR knu;
    KNOTVECTOR knv;
};
typedef struct surface_s* SURFACE;


struct res_nurbs_s{
    VECTOR pts;
    float u;
    float v;
    float d;
};
typedef struct res_nurbs_s RES_NURBS;



// taille de l'ecran
#define WIDTH 300
#define HEIGHT 300

// Parametres du ray marching
#define MAX_RAY_STEPS 128 // nombre max d'étape
#define DIST_MIN 0.01 // diatance a partir de laquel on a atteint un objet
#define MAX_TOTAL_LENGHT 500 // distance max que peut parcourir un rayon
#define EPSILON 0.0001 // pour le calcule des gradients
#define EPSILON_CRIT_NURBS 0.01 

#define NB_THREADS 12



#endif 