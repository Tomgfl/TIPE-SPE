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

float all_light(vector pts, vector source, res_SDF(*scene_actuelle)(vector));
float light_diffuse(vector pts, vector source, res_SDF(*scene_actuelle)(vector));

// float all_light_bvh(vector pts, BVHNode* scene, vector source, res_SDF(*scene_actuelle)(BVHNode*, vector, res_SDF));
// float light_diffuse_bvh(vector pts, BVHNode* scene, vector source, res_SDF(*scene_actuelle)(BVHNode*, vector, res_SDF));


// --- OMBRES --- //

float shadow_1(vector pts, vector source, res_SDF(*scene_act)(vector));
float shadow_2(vector pts, vector source, int k, res_SDF(*scene_act)(vector));

float brouillard(float t);
#endif