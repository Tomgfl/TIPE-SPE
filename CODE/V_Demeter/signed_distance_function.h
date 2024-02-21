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
RES_SDF SDF_sphere(VECTOR p, VECTOR centre, float rayon, COLOR couleur);
RES_SDF SDF_box(VECTOR p, VECTOR centre, float L, float l, float h, COLOR couleur);
RES_SDF SDF_cylindre(VECTOR p, VECTOR centre, float H, float r, COLOR couleur);
RES_SDF SDF_Cone(VECTOR p, VECTOR centre, float H, float r, COLOR couleur);
RES_SDF SDF_Pyramide(VECTOR p, VECTOR centre, float H, float c, COLOR couleur);
RES_SDF SDF_plan(VECTOR p, VECTOR n, VECTOR m, COLOR couleur);
RES_SDF SDF_Tor(VECTOR p, VECTOR centre, float R, float r, COLOR couleur);
RES_SDF SDF_Ellipsoid(VECTOR p, VECTOR centre, float a, float b, float c, COLOR couleur);
RES_SDF SDF_triangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c, COLOR couleur);
RES_SDF SDF_sphere_circonscrite_triangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c, COLOR couleur);

// SDF Pingouin
RES_SDF SDF_head(VECTOR p, VECTOR centre, float rayon);
RES_SDF SDF_corps(VECTOR p, VECTOR centre, float rayon);
RES_SDF SDF_Pingoo(VECTOR p, VECTOR centre, float rayon);

// Rotations
VECTOR rotation_x(VECTOR v, float angle);
VECTOR rotation_y(VECTOR v, float angle);
VECTOR rotation_z(VECTOR v, float angle);

// Operations
// RES_SDF min_sdf(RES_SDF d1, RES_SDF d2);
// RES_SDF max_sdf(RES_SDF d1, RES_SDF d2);
RES_SDF UnionSDF(RES_SDF d1, RES_SDF d2);
RES_SDF IntersectSDF(RES_SDF d1, RES_SDF d2);
RES_SDF SubstractSDF(RES_SDF d1, RES_SDF d2);
// Smooth
RES_SDF SmoothUnionSDF(RES_SDF d1, RES_SDF d2, float k);
RES_SDF SmoothIntersectSDF(RES_SDF d1, RES_SDF d2, float k);
RES_SDF SmoothSubstractSDF(RES_SDF d1, RES_SDF d2, float k);
// Modification de forme
RES_SDF Disturb(VECTOR p, RES_SDF d);



#endif 