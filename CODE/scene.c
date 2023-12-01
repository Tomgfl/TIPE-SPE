#include "scene.h"


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

// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
float MIN_ALL_SDF(coord pts){
    int nb = 1;
    float all_sdf[nb];

    //coord R_1 = {0.0, 7.0, 1.0}; float r_1 = 1.0; // caracteristique d'une sphere
    //coord R_2 = {1.5, 8.0, 0.5}; float r_2 = 0.5;
    //coord R_3 = {0.0, 9.0, 2.5}; float r_3 = 1.5;
    //coord C_1 = {-2.0, 7.0, 2.0}; float L_1 = 3.0; float l_1 = 1.0; float h_1 = 0.3;
    //coord T_1 = {0.0, 9.0, 2.5}; float Rt = 3; float rt = 0.2;
    // coord R_4 = {6, 10, 2};
    // coord R_5 = {-4, 6, 1};
    // vector n = {0.0, 0.0, 1.0};

    //float sdf_1 = SDF_sphere(pts, R_1, r_1);
    //float sdf_2 = SDF_sphere(pts, R_2, r_2);
    // float sdf_3 = SDF_sphere(pts, R_3, r_3);
    //float sdf_4 = SDF_box(pts, C_1, L_1, l_1, h_1);
    // float sdf_5 = SDF_Tor(pts, T_1, Rt, rt);    
    // float sdf_6 = SDF_plan(pts, n, 0.0);

    // float sdf_7 = SDF_box(pts, R_4, 2, 3, 1);

    // float sdf_8 = SDF_box(pts,R_5, 1, 1, 1);
    
    // float sdf_8 = mult_objects(pts);
    // all_sdf[0] = sdf_8;
    // all_sdf[0] = sdf_6;
    //// all_sdf[0] = sdf_3;
    // all_sdf[1] = sdf_5;
    //// all_sdf[2] = sdf_7;
    //// all_sdf[3] = sdf_8;

    // all_sdf[0] = sdf_3;
    // all_sdf[1] = sdf_5;
    // all_sdf[2] = sdf_6;

    // all_sdf[0] = mult_objects(pts);
    // all_sdf[0] = sdf_3;
    // all_sdf[0] = fractal_1_test(rotation_x(pts, 3.14/7.0));



    //all_sdf[2] = sdf_3;
    //all_sdf[3] = sdf_4;*/



    all_sdf[0] = scene_1(pts);

    return min_lst(all_sdf, nb);
}




