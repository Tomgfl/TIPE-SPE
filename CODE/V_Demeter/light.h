#ifndef LIGHT_H 
#define LIGHT_H


#include "options.h"
#include "utiles.h"
#include "vector.h"
#include "scene.h"
#include <time.h>



extern COLOR c_rouge;
extern COLOR c_bleu;
extern COLOR c_vert;
extern COLOR c_noir;
extern COLOR c_blanc;
extern COLOR c_gris;
extern COLOR c_fond;
extern COLOR c_jaune;

extern COLOR c_orange;
extern COLOR c_bistre;
extern COLOR c_bleu_berlin;

// --- LUMIERES --- //

float all_light(VECTOR pts, VECTOR source, RES_SDF(*scene_actuelle)(VECTOR));
float light_diffuse(VECTOR pts, VECTOR source, RES_SDF(*scene_actuelle)(VECTOR));

// --- OMBRES --- //

float shadow_1(VECTOR pts, VECTOR source, RES_SDF(*scene_act)(VECTOR));
float shadow_2(VECTOR pts, VECTOR source, int k, RES_SDF(*scene_act)(VECTOR));

float brouillard(float t);
#endif