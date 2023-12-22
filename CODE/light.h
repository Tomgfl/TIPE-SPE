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

float all_light(coord pts, coord source);
float light_diffuse(coord pts, coord source);

// --- OMBRES --- //

float shadow_1(coord pts, coord source);
float shadow_2(coord pts, coord source, int steps);

#endif