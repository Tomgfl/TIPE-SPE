#ifndef SIGNED_DISTANCE_FUNCTION_H 
#define SIGNED_DISTANCE_FUNCTION_H

#include <math.h>
#include "options.h"
#include "vector.h"
#include "utiles.h"
#include "light.h"
// #include <stdio.h>
// #include <stdlib.h>

// #include "signed_distance_function.h"
// #include "VECTOR.h"
// #include "utiles.h"
// #include "options.h"




// SDF
res_SDF SDF_sphere(VECTOR p, VECTOR centre, float rayon, color couleur);
res_SDF SDF_box(VECTOR p, VECTOR centre, float L, float l, float h, color couleur);
res_SDF SDF_cylindre(VECTOR p, VECTOR centre, float H, float r, color couleur);
res_SDF SDF_Cone(VECTOR p, VECTOR centre, float H, float r, color couleur);
res_SDF SDF_Pyramide(VECTOR p, VECTOR centre, float H, float c, color couleur);
res_SDF SDF_plan(VECTOR p, VECTOR n, VECTOR m, color couleur);
res_SDF SDF_Tor(VECTOR p, VECTOR centre, float R, float r, color couleur);
res_SDF SDF_Ellipsoid(VECTOR p, VECTOR centre, float a, float b, float c, color couleur);
res_SDF SDF_triangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c, color couleur);
res_SDF SDF_sphere_circonscrite_triangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c, color couleur);

// SDF Pingouin
res_SDF SDF_head(VECTOR p, VECTOR centre, float rayon);
res_SDF SDF_corps(VECTOR p, VECTOR centre, float rayon);
res_SDF SDF_Pingoo(VECTOR p, VECTOR centre, float rayon);

// Rotations
VECTOR rotation_x(VECTOR v, float angle);
VECTOR rotation_y(VECTOR v, float angle);
VECTOR rotation_z(VECTOR v, float angle);

// Operations
// res_SDF min_sdf(res_SDF d1, res_SDF d2);
// res_SDF max_sdf(res_SDF d1, res_SDF d2);
res_SDF UnionSDF(res_SDF d1, res_SDF d2);
res_SDF IntersectSDF(res_SDF d1, res_SDF d2);
res_SDF SubstractSDF(res_SDF d1, res_SDF d2);
// Smooth
res_SDF SmoothUnionSDF(res_SDF d1, res_SDF d2, float k);
res_SDF SmoothIntersectSDF(res_SDF d1, res_SDF d2, float k);
res_SDF SmoothSubstractSDF(res_SDF d1, res_SDF d2, float k);
// Modification de forme
res_SDF Disturb(VECTOR p, res_SDF d);



#endif 