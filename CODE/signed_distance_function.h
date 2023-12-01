#ifndef SIGNED_DISTANCE_FUNCTION_H 
#define SIGNED_DISTANCE_FUNCTION_H

#include "vector.h"




// rayon
struct ray_s{
    coord origine;
    vector direction;
};
typedef struct ray_s ray;





// SDF
float SDF_sphere(coord pts, coord centre, float rayon);
float SDF_box(coord p, coord centre, float L, float l, float h);
float SDF_cylindre(coord p, coord centre, float H, float r);
float SDF_Cone(coord p, coord centre, float H, float r);
float SDF_Pyramide(coord p, coord centre, float H, float c);
float SDF_plan(coord p, vector n, float h);
float SDF_Tor(coord p, coord centre, float R, float r);

// Rotations
coord rotation_x(coord v, float angle);
coord rotation_y(coord v, float angle);
coord rotation_z(coord v, float angle);

// Operations
float UnionSDF(float d1, float d2);
float IntersectSDF(float d1, float d2);
float SubstractSDF(float d1, float d2);
// Smooth
float SmoothUnionSDF(float d1, float d2, float k);
float SmoothIntersectSDF(float d1, float d2, float k);
float SmoothSubstractSDF(float d1, float d2, float k);



#endif 