#ifndef LIGHT_H 
#define LIGHT_H


#include "options.h"
#include "utiles.h"
#include "vector.h"
#include "scene.h"
#include <time.h>



extern color c_rouge;
extern color c_bleu;
extern color c_vert;
extern color c_noir;
extern color c_blanc;
extern color c_gris;
extern color c_fond;
extern color c_jaune;

extern color c_orange;
extern color c_bistre;
extern color c_bleu_berlin;

// --- LUMIERES --- //

float all_light(VECTOR pts, VECTOR source, res_SDF(*scene_actuelle)(VECTOR));
float light_diffuse(VECTOR pts, VECTOR source, res_SDF(*scene_actuelle)(VECTOR));

// --- OMBRES --- //

float shadow_1(VECTOR pts, VECTOR source, res_SDF(*scene_act)(VECTOR));
float shadow_2(VECTOR pts, VECTOR source, int k, res_SDF(*scene_act)(VECTOR));

float brouillard(float t);
#endif