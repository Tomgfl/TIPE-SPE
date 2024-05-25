#ifndef OPTION_H 
#define OPTION_H

#include <float.h>


// structs
// vecteur 3d
struct vector_s{
    float x, y, z;
};
typedef struct vector_s vector;

// --- COULEURS --- //
struct color_s{
    int r, g, b;
    float opp; // oppacité de la couleur 
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



// Objets 
struct objet_s{
    int type;         // Type d'objet : "0 = sphere", "1=tor", "2=cylindre", "3=cone", "4=pyramide", "5=box", "6=triangle", "7=ellipsoid"
    void* param;        // Paramètres de l'objet (h, l, L ...)
    float rayon;          // Rayon pour la boite englobante
    vector centre;      // Centre pour la boite englobante
    color couleur;
};
typedef struct objet_s OBJET;

struct param_sphere_s{
    vector centre;
    float rayon;
};
typedef struct param_sphere_s param_sphere;

struct param_tor_s{
    vector centre;
    float R;
    float r;
};
typedef struct param_tor_s param_tor;

struct param_cylindre_s{
    vector centre;
    float H;
    float r;
};
typedef struct param_cylindre_s param_cylindre;

struct param_cone_s{
    vector centre;
    float H;
    float r;
};
typedef struct param_cone_s param_cone;

struct param_pyramide_s{
    vector centre;
    float H;
    float c;
};
typedef struct param_pyramide_s param_pyramide;

struct param_box_s{
    vector centre;
    float L;
    float l;
    float h;
};
typedef struct param_box_s param_box;

struct param_triangle_s{
    vector a;
    vector b;
    vector c;
};
typedef struct param_triangle_s param_triangle;


struct param_ellipsoid_s{
    vector centre;
    float a;
    float b;
    float c;
};
typedef struct param_ellipsoid_s param_ellipsoid;


struct param_opdouble_s{
    OBJET o1;
    OBJET o2;
};
typedef struct param_opdouble_s param_opdouble;


struct param_opsimple_s{
    OBJET o1;
    float k;
};
typedef struct param_opsimple_s param_opsimple;

// BVH
typedef struct {
    vector centre;  // Centre de la boule englobante
    float r;        // Rayon de la boule
} BOULE;

typedef struct BVHNode_s BVHNode;
struct BVHNode_s {
    BOULE box; // Axis-Aligned Bounding Box (Boîte englobante alignée sur les axes)
    BVHNode* left;
    BVHNode* right;
    OBJET* obj; // Pointeur vers l'objet (ou un tableau d'objets) contenu dans ce nœud
    int obj_count; // Nombre d'objets contenu dans ce nœud
};

// Pour pthread
struct arg_s{
    res_SDF (*fct_scene_p)(vector);
    res_SDF (*fct_scene_bvh_fix)(BVHNode*, vector, res_SDF);
    res_SDF (*fct_scene_bvh_mov)(BVHNode*, vector);
    BVHNode* bvh;
    int id;             // id du thread
    ray** t_in;         // les rayons de l'ecran
    color** t_out;      // tab du resultat
    vector n;
    vector m;
    color c;
};
typedef struct arg_s arg;



// taille de l'ecran
#define WIDTH 1920
#define HEIGHT 1080

// Parametres du ray marching
#define MAX_RAY_STEPS 512 // nombre max d'étape
#define DIST_MIN 0.0001 // diatance a partir de laquel on a atteint un objet
#define MAX_TOTAL_LENGHT 500 // distance max que peut parcourir un rayon
#define EPSILON 0.00001 // pour le calcul des gradients

#define NB_THREADS 6



#endif 