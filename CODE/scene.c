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
    float sdf_box = SDF_box(pts, C_1, 4,4,4);

    coord C_2 = {-10,10,10};
    float sdf_sphere = SDF_sphere(pts, C_2, 2);

    coord C_3 = {10,10,0};
    float sdf_tor = SDF_Tor(pts, C_3, 2, 1);

    coord C_4 = {0,10,10};
    float sdf_cylindre = SDF_cylindre(pts, C_4, 6, 1);

    coord C_5 = {0,10,0};
    float sdf_cone = SDF_Cone(pts, C_5, 6, 2);


    all_sdf[0] = sdf_plan;
    all_sdf[1] = sdf_tor;
    all_sdf[2] = sdf_box;
    all_sdf[3] = sdf_cylindre;
    all_sdf[4] = sdf_cone;
    all_sdf[5] = sdf_sphere;

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

    coord C_3 = {-4,8,15};
    float sdf_tor = SDF_Tor(rotation_x((coord){pts.x-C_3.x,pts.y-C_3.y,pts.z-C_3.z},time_scene), (coord){0,0,0}, 2, 1);
    

    // all_sdf[0] = sdf_plan;
    all_sdf[0] = sdf_box;
    all_sdf[1] = sdf_sphere;
    all_sdf[2] = sdf_tor;

    return min_lst(all_sdf, nb);
}



// --- SCENE #3 --- //
float scene_3(coord pts){
    int nb = 4;
    float all_sdf[nb];

    coord C_1 = {15,25,15};
    float sdf_box = SDF_box(pts, C_1, 10,10,10);

    coord C_2 = {15,25,15};
    float sdf_sphere = SDF_sphere(pts, C_2, 6.5);


    coord C_3 = {15,25,-5};
    float sdf_box2 = SDF_box(pts, C_3, 10,10,10);

    coord C_4 = {15,25,-5};
    float sdf_sphere2 = SDF_sphere(pts, C_4, 6.5);


    coord C_5 = {-15,25,15};
    float sdf_box3 = SDF_box(pts, C_5, 10,10,10);

    coord C_6 = {-15,25,15};
    float sdf_sphere3 = SDF_sphere(pts, C_6, 6.5);


    coord C_7 = {-15,25,-5};
    float sdf_box4 = SDF_box(pts, C_7, 12,12,12);

    coord C_8 = {-15,25,-5};
    float sdf_sphere4 = SDF_sphere(pts, C_8, 6);



    all_sdf[0] = IntersectSDF(sdf_box, sdf_sphere);
    all_sdf[1] = SmoothUnionSDF(sdf_box2, sdf_sphere2,1);
    all_sdf[2] = SubstractSDF(sdf_box3, sdf_sphere3);
    all_sdf[3] = SubstractSDF(sdf_sphere4, sdf_box4);



    return min_lst(all_sdf, nb);
}


// --- SCENE #4 --- // Test ellipsoid
float scene_4(coord pts){
    int nb = 1;
    float all_sdf[nb];

    coord C_1 = {-5,10,15};
    float sdf_ellipsoid = SDF_Ellipsoid(rotation_z((coord){pts.x-C_1.x,pts.y-C_1.y,pts.z-C_1.z}, time_scene), (coord){0,0,0}, 2,3,5);

    all_sdf[0] = sdf_ellipsoid;

    return min_lst(all_sdf, nb);
}




// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
float SCENE_PRINCIPAL(coord pts){

    return scene_4(pts);

}




