#ifndef UTILES_H 
#define UTILES_H

// #include "signed_distance_function.h"

#include "options.h"
#include "signed_distance_function.h"
#include "objets.h"

float min_lst (float* lst, int n);
float MIN(float x, float y);
float MAX(float x, float y);

// struct res_SDF;


res_SDF min_lst_sdf(res_SDF* lst, int n);
res_SDF min_sdf(res_SDF d1, res_SDF d2);
res_SDF max_sdf(res_SDF d1, res_SDF d2);

OBJET min_lst_obj(OBJET* lst, int n, vector p);




res_systeme_2 solve_systeme_2(float a, float b, float c, float d, float alpha, float beta);

#endif 