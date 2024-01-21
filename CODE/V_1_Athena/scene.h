#ifndef SCENE_H 
#define SCENE_H

#include "options.h"
#include "pingouin_sdf.h"
// #include "3d_obj/pingouin_2_sdf.h"
// #include "3d_obj/cube_sdf.h"
#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"
// #include <stdio.h>
// #include "3d_obj/pingouin_1_sdf.h"


res_SDF scene_1(vector pts);
res_SDF scene_effets(vector pts);
res_SDF banquise(vector pts);

// res_SDF SCENE_PRINCIPAL(vector pts);
res_SDF scene_sphere(vector pts);



#endif 