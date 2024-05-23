#include "scene.h"
#include "bvh.h"
#include "simpsons_bvh.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>



extern float time_scene;



extern float time_scene;


res_SDF scene_1(vector pts){
    int nb = 4;
    res_SDF* all_sdf = malloc(nb*sizeof(res_SDF));

    OBJET obj4 = BuildSphere((vector){100, 20*sin(time_scene/2), 20*cos(time_scene/2)}, 3, c_blanc);
    OBJET obj5 = BuildSphere((vector){100, 20*sin(time_scene/3), 20*cos(time_scene/3)}, 3, c_blanc);
    OBJET obj6 = BuildSphere((vector){100, 20*sin(time_scene/4), 20*cos(time_scene/4)}, 3, c_blanc);
    OBJET obj7 = BuildSphere((vector){100, 20*sin(time_scene/5), 20*cos(time_scene/5)}, 3, c_blanc);
    res_SDF sdf_sph1 = SDF_Objet(pts, obj4);
    FreeObj(obj4);
    res_SDF sdf_sph2 = SDF_Objet(pts, obj5);
    FreeObj(obj5);
    res_SDF sdf_sph3 = SDF_Objet(pts, obj6);
    FreeObj(obj6);
    res_SDF sdf_sph4 = SDF_Objet(pts, obj7);
    FreeObj(obj7);


    all_sdf[0] = sdf_sph1;
    all_sdf[1] = sdf_sph2;
    all_sdf[2] = sdf_sph3;
    all_sdf[3] = sdf_sph4;
    res_SDF res = min_lst_sdf(all_sdf, nb);
    free(all_sdf);
    return res;
}

BVHNode* scene1_bvh () {

    int nb = 4;
    OBJET* all_obj = malloc(nb*sizeof(OBJET));
    all_obj[0] = BuildSphere((vector){100, 20*sin(time_scene/2), 20*cos(time_scene/2)}, 3, c_blanc);
    all_obj[1] = BuildSphere((vector){100, 20*sin(time_scene/3), 20*cos(time_scene/3)}, 3, c_blanc);
    all_obj[2] = BuildSphere((vector){100, 20*sin(time_scene/4), 20*cos(time_scene/4)}, 3, c_blanc);
    all_obj[3] = BuildSphere((vector){100, 20*sin(time_scene/5), 20*cos(time_scene/5)}, 3, c_blanc);

    BVHNode* root = buildBVH(all_obj, nb);

    return root;
}


BVHNode* TestBanquise () {
    int nb = 4;
    OBJET* all_obj = malloc(nb*sizeof(OBJET));
    all_obj[0] = BuildBox((vector){0,10,-10}, 500, 500, 20, c_blanc);
    all_obj[1] = BuildSphere((vector){10, 70, 5}, 20, c_iceberg);
    all_obj[2] = BuildRotY(BuildTor((vector){10, 40, 10}, 7, 2, c_iceberg), 2);
    all_obj[3] = BuildSphere((vector){10, 40, 10}, 2, c_rouge);

    BVHNode* root = buildBVH(all_obj, nb);
    return root;
}

res_SDF scene_banquise(vector pts){
    int nb = 4;
    res_SDF all_sdf[nb];


    OBJET obj1 = BuildBox((vector){0,10,-10}, 500, 500, 20, c_blanc);
    res_SDF sdf_box1 = SDF_Objet(pts, obj1);
    FreeObj(obj1);
    OBJET obj2 = BuildSphere((vector){10, 70, 5}, 20, c_iceberg);
    res_SDF sdf_cyl = SDF_Objet(pts, obj2);
    FreeObj(obj2);
    OBJET obj3 = BuildTor((vector){10, 40, 10}, 7, 2, c_iceberg);
    OBJET obj4 = BuildRotX(obj3, 0);
    res_SDF sdf_tri = SDF_Objet(pts, obj4);
    FreeObj(obj3);
    FreeObj(obj4);
    OBJET obj5 = BuildSphere((vector){10, 40, 10}, 2, c_rouge);
    res_SDF sdf_sph = SDF_Objet(pts, obj5);
    FreeObj(obj5);

    all_sdf[0] = sdf_box1;
    all_sdf[1] = sdf_cyl;
    all_sdf[2] = sdf_tri;
    all_sdf[3] = sdf_sph;
    
    // all_sdf[6] = sdf_ell;
    return min_lst_sdf(all_sdf, nb);
}



BVHNode* SceneWindows () {  // A regarder par dessus
    int nb = 4;
    OBJET* all_obj = malloc(nb*sizeof(OBJET));
    all_obj[0] = BuildSphere((vector){100, 20*sin(time_scene/2), 20*cos(time_scene/2)}, 3, c_blanc);
    all_obj[1] = BuildSphere((vector){100, 20*sin(time_scene/3), 20*cos(time_scene/3)}, 3, c_blanc);
    all_obj[2] = BuildSphere((vector){100, 20*sin(time_scene/4), 20*cos(time_scene/4)}, 3, c_blanc);
    all_obj[3] = BuildSphere((vector){100, 20*sin(time_scene/5), 20*cos(time_scene/5)}, 3, c_blanc);

    BVHNode* root = buildBVH(all_obj, nb);
    return root;
}



// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
res_SDF SCENE_PRINCIPALE(vector pts){
    return scene_1(pts);
    // return SDF_pingouin_2(rotation_x(rotation_z(pts, -50),270),pts);
}


res_SDF SCENE_BVH(BVHNode* scene, vector pts, res_SDF Plan){
    res_SDF res = traverseBVH(scene, pts, Plan);
    return res;
}


res_SDF SCENE_BANQUISE(vector pts){
    return scene_banquise(pts);
    // return SDF_pingouin_2(rotation_x(rotation_z(pts, -50),270),pts);
}
res_SDF SCENE_BVH_Bis(BVHNode* scene, vector pts){
    res_SDF res = traverseBVH(scene, pts, (res_SDF){FLT_MAX,c_rouge});
    return res;
}

BVHNode* SCENE_MOUVANTE() {
    return BVH_Maison();
}

BVHNode* Scene_Simpson_Test() {
    return BVH_Maison();
}

res_SDF Test_Simpsons(vector pts){
    res_SDF maxsdf = (res_SDF){FLT_MAX, c_blanc};
    BVHNode* a = Scene_Simpson_Test();
    res_SDF res = traverseBVH(a, pts, maxsdf);
    freeBVH(a);
    return res;
}




