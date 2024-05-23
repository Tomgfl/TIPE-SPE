#ifndef SCENE_H 
#define SCENE_H

#include "options.h"
#include "simpsons_bvh.h"
#include "plage_bvh.h"
// #include "3d_obj/pingouin_2_sdf.h"
// #include "3d_obj/cube_sdf.h"
#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"
#include "objets.h"
#include "bvh.h"

// #include <stdio.h>
// #include "3d_obj/pingouin_1_sdf.h"

// res_SDF SDF_pingouin(vector pts, vector c);

res_SDF scene_1(vector pts);
BVHNode* scene1_bvh () ;
BVHNode* TestBanquise () ;
res_SDF scene_banquise(vector pts);
// res_SDF scene_effets(vector pts);
// res_SDF banquise(vector pts);
// res_SDF paysage(vector pts);

res_SDF SCENE_PRINCIPALE(vector pts);
res_SDF SCENE_BANQUISE(vector pts);
res_SDF SCENE_BVH(BVHNode* scene, vector pts, res_SDF Plan);
res_SDF SCENE_BVH_Bis(BVHNode* scene, vector pts);


// res_SDF scene_sphere(vector pts);
BVHNode* SceneBouge();
BVHNode* SceneWindows ();  // A regarder par dessus
// res_SDF SCENE_FIXE(vector pts);
BVHNode* SCENE_MOUVANTE();

BVHNode* Scene_Simpson_Test();
res_SDF Test_Simpsons(vector pts);

#endif 