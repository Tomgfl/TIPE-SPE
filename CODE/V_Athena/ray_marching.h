#ifndef RAY_MARCHING_H 
#define RAY_MARCHING_H

#include <time.h>
#include "options.h"
#include "light.h"
// #include "signed_distance_function.h"
#include "vector.h"
#include "scene.h"



color ray_marching(ray r, res_SDF (*scene_actuelle)(vector));
color ray_marching_paysage(ray r, res_SDF (*scene_actuelle)(vector));



#endif 