#ifndef RAY_MARCHING_H 
#define RAY_MARCHING_H

#include "light.h"
// #include "signed_distance_function.h"
#include "options.h"
#include "vector.h"
#include "scene.h"

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

color ray_marching(ray r);

#endif 