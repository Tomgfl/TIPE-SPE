#ifndef SIGNED_DISTANCE_FUNCTION_H 
#define SIGNED_DISTANCE_FUNCTION_H

#include <math.h>
#include "options.h"
#include "vector.h"
#include "utiles.h"
#include "light.h"
#include "objets.h"
// #include <stdio.h>
// #include <stdlib.h>

// #include "signed_distance_function.h"
// #include "vector.h"
// #include "utiles.h"
// #include "options.h"




// SDF
res_SDF SDF_Objet(vector p, OBJET obj);
res_SDF SDF_plan(vector p, vector n, vector m, color couleur);
res_SDF SDF_sphere(vector p, void* param, color couleur);
res_SDF SDF_box(vector p, void* param, color couleur);
res_SDF SDF_cylindre(vector p, void* param, color couleur);
res_SDF SDF_Cone(vector p, void* param, color couleur);
res_SDF SDF_Pyramide(vector p, void* param, color couleur);
res_SDF SDF_Tor(vector p, void* param, color couleur);
res_SDF SDF_Ellipsoid(vector p, void* param, color couleur);
res_SDF SDF_triangle(vector p, void* param, color couleur);
res_SDF SDF_sphere_circonscrite_triangle(vector p, void* param, color couleur);

// SDF Pingouin
// res_SDF SDF_head(vector p, vector centre, float rayon);
// res_SDF SDF_corps(vector p, vector centre, float rayon);
// res_SDF SDF_Pingoo(vector p, vector centre, float rayon);

// Rotations
vector rotation_x(vector v, float angle);
vector rotation_y(vector v, float angle);
vector rotation_z(vector v, float angle);

// Operations
// res_SDF min_sdf(res_SDF d1, res_SDF d2);
// res_SDF max_sdf(res_SDF d1, res_SDF d2);
res_SDF UnionSDF (vector p, void* param); 
res_SDF IntersectSDF (vector p, void* param);
res_SDF SubstractSDF (vector p, void* param);
// Smooth
// res_SDF SmoothUnionSDF(res_SDF d1, res_SDF d2, float k);
// res_SDF SmoothIntersectSDF(res_SDF d1, res_SDF d2, float k);
// res_SDF SmoothSubstractSDF(res_SDF d1, res_SDF d2, float k);
// Modification de forme
// res_SDF Disturb(vector p, res_SDF d);

// Pour objet


#endif 