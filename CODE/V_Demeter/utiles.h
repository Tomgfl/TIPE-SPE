#ifndef UTILES_H 
#define UTILES_H

// #include "signed_distance_function.h"

#include "options.h"
#include <stdlib.h>
#include <assert.h>

float min_lst (float* lst, int n);
// float MIN(float x, float y);
// float MAX(float x, float y);

// struct res_SDF;


RES_SDF min_lst_sdf(RES_SDF* lst, int n);
RES_SDF min_sdf(RES_SDF d1, RES_SDF d2);
RES_SDF max_sdf(RES_SDF d1, RES_SDF d2);

float** create_2d_tab(int n, int m, float val);
void free_tab_2d(float** tab, int n);


RES_SYS_2 solve_systeme_2(float a, float b, float c, float d, float alpha, float beta);

float det_mat_3(float* mat);
VECTOR inv_mat_3_x_vect(float* mat, VECTOR X);

#endif 