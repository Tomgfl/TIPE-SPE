#ifndef SCENE_H 
#define SCENE_H

#include "options.h"
#include "pingouin_sdf.h"
// #include "3d_obj/pingouin_2_sdf.h"
// #include "3d_obj/cube_sdf.h"
#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"
#include "nurbs.h"
// #include <stdio.h>
// #include "3d_obj/pingouin_1_sdf.h"

// RES_SDF SDF_pingouin(vector pts, vector c);

RES_SDF scene_1(VECTOR pts);
RES_SDF scene_effets(VECTOR pts);
RES_SDF banquise(VECTOR pts);
RES_SDF nurbs_scene(VECTOR pts);


// RES_SDF SCENE_PRINCIPAL(vector pts);
RES_SDF scene_sphere(VECTOR pts);



#endif 