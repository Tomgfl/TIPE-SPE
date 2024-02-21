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

// res_SDF SDF_pingouin(vector pts, vector c);

res_SDF scene_1(VECTOR pts);
res_SDF scene_effets(VECTOR pts);
res_SDF banquise(VECTOR pts);
res_SDF nurbs_scene(VECTOR pts);


// res_SDF SCENE_PRINCIPAL(vector pts);
res_SDF scene_sphere(VECTOR pts);



#endif 