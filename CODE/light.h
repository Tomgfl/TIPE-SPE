#ifndef LIGHT_H 
#define LIGHT_H

#include "vector.h"

// --- COULEURS --- //
struct color_s{
    int r, g, b;
    float opp; // oppaciter de la couleur 
};
typedef struct color_s color;




// --- LUMIERES --- //

float all_light(vector pts, vector source);
float light_diffuse(vector pts, vector source);

// --- OMBRES --- //

float shadow_1(vector pts, vector source);
float shadow_2(vector pts, vector source, int steps);

#endif