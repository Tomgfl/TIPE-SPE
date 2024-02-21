#ifndef RAY_MARCHING_H 
#define RAY_MARCHING_H

#include <time.h>
#include "options.h"
#include "light.h"
// #include "signed_distance_function.h"
#include "vector.h"
#include "scene.h"

COLOR ray_marching(RAY r, RES_SDF (*scene_actuelle)(VECTOR));
void* ray_marching_thread(void* ptr_args);

#endif 