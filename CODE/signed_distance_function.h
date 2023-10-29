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

float MIN_ALL_SDF(coord pts);


#endif 