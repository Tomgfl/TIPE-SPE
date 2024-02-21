#ifndef NURBS_H 
#define NURBS_H

#define EPS_1 0.001
#define EPS_2 0.001
#define MAX_ITERATIONS 100

#include "options.h"
#include "math.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// --- FONCTIONS D'INITIALISATIONS --- //
CNET create_cnet(int n, int m);
void free_cnet(CNET net);
KNOTVECTOR create_knotvector(int m);
void free_knotvector(KNOTVECTOR knot);
SURFACE create_surface(int p, int q);
void free_surface(SURFACE surf);


// --- FONCTIONS DE BASE --- //
float N_nurbs(int i, int p, float u, KNOTVECTOR U);
VECTOR R_nurbs(float u, float v, SURFACE s);
float D_nurbs(float u, float v, SURFACE s);
VECTOR S_nurbs(float u, float v, SURFACE s);
// float dN_nurbs(int i, int p, float u, KNOTVECTOR U);
// vector dR_u_nurbs(float u, float v, SURFACE s);
// vector dR_v_nurbs(float u, float v, SURFACE s);
// float dD_u_nurbs(float u, float v, SURFACE s);
// float dD_v_nurbs(float u, float v, SURFACE s);
float dkN_nurbs(int k, int i, int p, float u, KNOTVECTOR U);
VECTOR dR_ku_lv_nurbs(int k, int l, float u, float v, SURFACE s);
float dD_ku_lv_nurbs(int k, int l, float u, float v, SURFACE s);
VECTOR S_u_nurbs(float u, float v, SURFACE s);
VECTOR S_v_nurbs(float u, float v, SURFACE s);
VECTOR S_uv_nurbs(float u, float v, SURFACE s);
VECTOR S_uu_nurbs(float u, float v, SURFACE s);
VECTOR S_vv_nurbs(float u, float v, SURFACE s);


// --- Projection --- //
VECTOR r_nurbs(float u, float v, SURFACE s, VECTOR P);
float f_nurbs(float u, float v, SURFACE s, VECTOR P);
float g_nurbs(float u, float v, SURFACE s, VECTOR P);
float f_u_nurbs(float u, float v, SURFACE s, VECTOR P);
float f_v_nurbs(float u, float v, SURFACE s, VECTOR P);
float g_u_nurbs(float u, float v, SURFACE s, VECTOR P);
float g_v_nurbs(float u, float v, SURFACE s, VECTOR P);
float det_sys(float u, float v, SURFACE s, VECTOR P);
float next_ui(float u, float v, float det, SURFACE s, VECTOR P);
float next_vi(float u, float v, float det, SURFACE s, VECTOR P);
bool crit_1(float u, float v, SURFACE s, VECTOR P);
bool crit_2(float u, float v, SURFACE s, VECTOR P);
VECTOR projection_nurbs(SURFACE s, VECTOR P);
// float dist_nurbs(SURFACE s, vector P);



// --- NURBS --- //
SURFACE nurbs_1();
SURFACE nurbs_2();
void affiche_surface(SURFACE s);






#endif 