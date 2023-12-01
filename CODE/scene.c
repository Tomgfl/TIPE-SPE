#include "scene.h"

extern float time_scene;

// --- SCENE --- //


// --- SCENE #1 --- // Tous les objets
float scene_1(coord pts){
    int nb = 6;
    float all_sdf[nb];

    vector n_plan = {0, 0, 1};
    float sdf_plan = SDF_plan(pts, n_plan, -4);

    coord C_1 = {-10,10,0};
    float sdf_box = SDF_box(pts, C_1, 3,3,3);

    coord C_2 = {10,10,0};
    float sdf_sphere = SDF_sphere(pts, C_2, 3);

    coord C_3 = {-10,10,10};
    float sdf_tor = SDF_Tor(pts, C_3, 2, 1);

    coord C_4 = {0,10,10};
    float sdf_cylindre = SDF_cylindre(pts, C_4, 6, 1);

    coord C_5 = {0,10,0};
    float sdf_cone = SDF_Cone(pts, C_5, 6, 2);


    all_sdf[0] = sdf_plan;
    all_sdf[1] = sdf_box;
    all_sdf[2] = sdf_sphere;
    all_sdf[3] = sdf_tor;
    all_sdf[4] = sdf_cylindre;
    all_sdf[5] = sdf_cone;

    return min_lst(all_sdf, nb);
}


float scene_2(coord pts){
    int nb = 3;
    float all_sdf[nb];

    // vector n_plan = {0, 0, 1};
    // float sdf_plan = SDF_plan(pts, n_plan, -4);

    coord C_1 = {-10,10,0};
    float sdf_box = SDF_box(pts, C_1, 3,3,3);

    coord C_2 = {10,10,0};
    float sdf_sphere = SDF_sphere(pts, C_2, 3);

    coord C_3 = {-10,10,10};
    float sdf_tor = SDF_Tor(rotation_y(pts,time_scene), C_3, 2, 1);


    // all_sdf[0] = sdf_plan;
    all_sdf[0] = sdf_box;
    all_sdf[1] = sdf_sphere;
    all_sdf[2] = sdf_tor;

    return min_lst(all_sdf, nb);
}

// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
float SCENE_PRINCIPAL(coord pts){

    return scene_2(pts);

}




