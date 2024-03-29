#ifndef RAY_MARCHING_H 
#define RAY_MARCHING_H

#include <time.h>
#include "options.h"
#include "light.h"
// #include "signed_distance_function.h"
#include "vector.h"
#include "scene.h"
#include "bvh.h"
#include "objets.h"

color ray_marching(ray r, res_SDF (*scene_actuelle)(vector));
color ray_marching_bvh(ray r, BVHNode* scene, res_SDF (*scene_actuelle)(vector), res_SDF (*scene_bvh)(BVHNode*, vector, res_SDF), vector n, vector m, color c);
color ray_marching_bvhNoPlan(ray r, BVHNode* scene, res_SDF (*scene_actuelle)(vector), res_SDF (*scene_bvh)(BVHNode*, vector));
color ray_marching_bvh_moving(ray r, BVHNode* scene, res_SDF (*scene_actuelle)(vector), res_SDF (*scene_bvh)(BVHNode*, vector));
void* ray_marching_bvh_thread(void* ptr_args);

#endif 