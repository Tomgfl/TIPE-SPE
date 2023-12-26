#ifndef SIGNED_DISTANCE_FUNCTION_H 
#define SIGNED_DISTANCE_FUNCTION_H

#include "vector.h"




// rayon
struct ray_s{
    vector origine;
    vector direction;
};
typedef struct ray_s ray;





// SDF
float SDF_sphere(vector p, vector centre, float rayon);
float SDF_box(vector p, vector centre, float L, float l, float h);
float SDF_cylindre(vector p, vector centre, float H, float r);
float SDF_Cone(vector p, vector centre, float H, float r);
float SDF_Pyramide(vector p, vector centre, float H, float c);
float SDF_plan(vector p, vector n, vector m);
float SDF_Tor(vector p, vector centre, float R, float r);
float SDF_Ellipsoid(vector p, vector centre, float a, float b, float c);
float SDF_triangle(vector p, vector a, vector b, vector c);
float SDF_sphere_circonscrite_triangle(vector p, vector a, vector b, vector c);

// SDF Pingouin
float SDF_head(vector p, vector centre, float rayon);
float SDF_corps(vector p, vector centre, float rayon);
float SDF_Pingoo(vector p, vector centre, float rayon);

// Rotations
vector rotation_x(vector v, float angle);
vector rotation_y(vector v, float angle);
vector rotation_z(vector v, float angle);

// Operations
float UnionSDF(float d1, float d2);
float IntersectSDF(float d1, float d2);
float SubstractSDF(float d1, float d2);
// Smooth
float SmoothUnionSDF(float d1, float d2, float k);
float SmoothIntersectSDF(float d1, float d2, float k);
float SmoothSubstractSDF(float d1, float d2, float k);



#endif 