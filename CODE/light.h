#ifndef LIGHT_H 
#define LIGHT_H


#include "utiles.h"
// #include "options.h"
#include "vector.h"
#include "scene.h"

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

extern color c_rouge;
extern color c_bleu;
extern color c_vert;
extern color c_noir;
extern color c_blanc;
extern color c_gris;
extern color c_fond;

// --- LUMIERES --- //

float all_light(vector pts, vector source);
float light_diffuse(vector pts, vector source);

// --- OMBRES --- //

float shadow_1(vector pts, vector source);
float shadow_2(vector pts, vector source, int steps);

#endif