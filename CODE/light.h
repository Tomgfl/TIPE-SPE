#ifndef LIGHT_H 
#define LIGHT_H


#include "options.h"
#include "utiles.h"
#include "vector.h"
#include "scene.h"



extern color c_rouge;
extern color c_bleu;
extern color c_vert;
extern color c_noir;
extern color c_blanc;
extern color c_gris;
extern color c_fond;

extern color c_orange;
extern color c_bistre;
extern color c_bleu_berlin;

// --- LUMIERES --- //

float all_light(vector pts, vector source);
float light_diffuse(vector pts, vector source);

// --- OMBRES --- //

float shadow_1(vector pts, vector source);
float shadow_2(vector pts, vector source, int steps);

#endif