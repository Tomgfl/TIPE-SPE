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
extern color c_iceberg;

extern color c_canape;
extern color c_trombone;
extern color c_bouton;
extern color c_commode;
extern color c_sol;
extern color c_mur;
extern color c_tp1;
extern color c_tp2;
extern color c_tp3;
extern color c_tp4;
extern color c_corbeille;
extern color c_tel;
extern color c_l2;
extern color c_a2;
extern color c_tige;
extern color c_l3;
extern color c_table1;
extern color c_table2;


// --- LUMIERES --- //

float all_light(vector pts, vector source, BVHNode* scene);
float light_diffuse(vector pts, vector source, BVHNode* scene);

// float all_light_bvh(vector pts, BVHNode* scene, vector source, res_SDF(*scene_actuelle)(BVHNode*, vector, res_SDF));
// float light_diffuse_bvh(vector pts, BVHNode* scene, vector source, res_SDF(*scene_actuelle)(BVHNode*, vector, res_SDF));


// --- OMBRES --- //

float shadow_1(vector pts, vector source, BVHNode* scene);
float shadow_2(vector pts, vector source, int k, BVHNode* scene);

float brouillard(float t);
#endif