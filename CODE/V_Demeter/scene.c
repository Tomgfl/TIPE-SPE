#include "scene.h"

extern float time_scene;

// --- SCENE --- //
RES_SDF scene_sphere(VECTOR pts){
    int nb = 1;
    RES_SDF all_sdf[nb];

    VECTOR C = {0,0,7};
    RES_SDF sdf_sphere = SDF_sphere(pts, C, 2, c_orange);
    sdf_sphere = Disturb(pts, sdf_sphere);

    return sdf_sphere;

}

// --- SCENE #1 --- // Tous les objets
RES_SDF scene_1(VECTOR pts){
    int nb = 6;
    RES_SDF all_sdf[nb];

    VECTOR n_plan = {0, 0, 1};
    RES_SDF sdf_plan = SDF_plan(pts, n_plan, (VECTOR){0,0,-4}, c_gris);

    VECTOR C_1 = {-10,10,0};
    RES_SDF sdf_box = SDF_box(pts, C_1, 4,4,4, c_bleu);

    VECTOR C_2 = {-10,10,10};
    RES_SDF sdf_sphere = SDF_sphere(pts, C_2, 2, c_blanc);

    VECTOR C_3 = {10,10,0};
    RES_SDF sdf_tor = SDF_Tor(pts, C_3, 2, 1, c_bleu_berlin);
    sdf_tor = Disturb(pts, sdf_tor);

    VECTOR C_4 = {0,10,10};
    RES_SDF sdf_tri = SDF_triangle(pts, (VECTOR){-3,10,8},(VECTOR){3,10,10},(VECTOR){0,10,13},c_vert);
    // RES_SDF sdf_cylindre = SDF_cylindre(pts, C_4, 6, 1, c_bistre);

    VECTOR C_5 = {0,10,0};
    RES_SDF sdf_ell = SDF_Ellipsoid(pts, C_5, 3.2, 1.0, 1.6, c_orange);
    // RES_SDF sdf_cone = SDF_Cone(pts, C_5, 6, 2, c_noir);


    all_sdf[0] = sdf_plan;
    all_sdf[1] = sdf_tor;
    all_sdf[2] = sdf_box;
    all_sdf[3] = sdf_tri;
    all_sdf[4] = sdf_ell;
    all_sdf[5] = sdf_sphere;

    return min_lst_sdf(all_sdf, nb);
}



RES_SDF scene_effets(VECTOR pts){
    int nb = 1;
    RES_SDF all_sdf[nb];

    VECTOR C_1 = {15,-2,12};
    RES_SDF sphere_1 = SDF_sphere(pts, C_1, 4.0, c_orange);
    sphere_1 = Disturb(pts, sphere_1);

    all_sdf[0] = sphere_1;

    return min_lst_sdf(all_sdf, nb);
}

RES_SDF banquise(VECTOR pts){
    
    return SDF_pingouin(rotation_y(rotation_x(pts, 90), 35), pts);
}





RES_SDF nurbs_scene(VECTOR pts){
    // SURFACE surf = nurbs_2();
    SURFACE surf = nurbs_rd();

    // affiche_surface(nurbs_test);

    RES_SDF N;
    // N.dist = norm_vector(v_sub(pts,projection_nurbs_3(surf, pts, 0,1,0,1, 2, 10)));
    // N.dist = norm_vector(v_sub(pts,projection_nurbs_4(surf, pts, 3, 10)));
    N.c = c_orange;

    // RES_SDF res = min_sdf(res, dist_c_net(surf->net, pts));
    RES_SDF res = dist_c_net(surf->net, pts);

    free_surface(surf);

    // RES_SDF A = SDF_sphere(pts, (VECTOR){-6,-4,0},0.5, c_vert);
    // RES_SDF B = SDF_sphere(pts, (VECTOR){-6,5,0},0.5, c_vert);
    // RES_SDF C = SDF_sphere(pts, (VECTOR){4,5,0},0.5, c_vert);
    // RES_SDF D = SDF_sphere(pts, (VECTOR){4,-4,0},0.5, c_vert);

    // RES_SDF E = min_sdf(min_sdf(A,B),min_sdf(C,D));
    // if (res.dist < E.dist){
    //     printf("ok\n");
    // }
    

    // return min_sdf(min_sdf(A,B),min_sdf(C,D));
    return res;
}






// float scene_2(vector pts){
//     int nb = 3;
//     float all_sdf[nb];

//     // vector n_plan = {0, 0, 1};
//     // float sdf_plan = SDF_plan(pts, n_plan, -4);
    

//     vector C_1 = {-10,10,0};
//     float sdf_box = SDF_box(pts, C_1, 3,3,3);

//     vector C_2 = {10,10,0};
//     float sdf_sphere = SDF_sphere(pts, C_2, 3);

//     vector C_3 = {-4,8,15};
//     float sdf_tor = SDF_Tor(rotation_x((vector){pts.x-C_3.x,pts.y-C_3.y,pts.z-C_3.z},time_scene), (vector){0,0,0}, 2, 1);

    

//     // all_sdf[0] = sdf_plan;
//     all_sdf[0] = sdf_box;
//     all_sdf[1] = sdf_sphere;
//     all_sdf[2] = sdf_tor;

//     return min_lst(all_sdf, nb);
// }



// // --- SCENE #3 --- //
// float scene_3(vector pts){
//     int nb = 4;
//     float all_sdf[nb];

//     vector C_1 = {15,25,15};
//     float sdf_box = SDF_box(pts, C_1, 10,10,10);

//     vector C_2 = {15,25,15};
//     float sdf_sphere = SDF_sphere(pts, C_2, 6.5);


//     vector C_3 = {15,25,-5};
//     float sdf_box2 = SDF_box(pts, C_3, 10,10,10);

//     vector C_4 = {15,25,-5};
//     float sdf_sphere2 = SDF_sphere(pts, C_4, 6.5);


//     vector C_5 = {-15,25,15};
//     float sdf_box3 = SDF_box(pts, C_5, 10,10,10);

//     vector C_6 = {-15,25,15};
//     float sdf_sphere3 = SDF_sphere(pts, C_6, 6.5);


//     vector C_7 = {-15,25,-5};
//     float sdf_box4 = SDF_box(pts, C_7, 12,12,12);

//     vector C_8 = {-15,25,-5};
//     float sdf_sphere4 = SDF_sphere(pts, C_8, 6);



//     all_sdf[0] = IntersectSDF(sdf_box, sdf_sphere);
//     all_sdf[1] = SmoothUnionSDF(sdf_box2, sdf_sphere2,1);
//     all_sdf[2] = SubstractSDF(sdf_box3, sdf_sphere3);
//     all_sdf[3] = SubstractSDF(sdf_sphere4, sdf_box4);



//     return min_lst(all_sdf, nb);
// }


// // --- SCENE #4 --- // Test ellipsoid
// float scene_4(vector pts){
//     int nb = 1;
//     float all_sdf[nb];

//     vector C_1 = {-5,10,15};
//     float sdf_ellipsoid = SDF_Ellipsoid(rotation_z((vector){pts.x-C_1.x,pts.y-C_1.y,pts.z-C_1.z}, time_scene), (vector){0,0,0}, 2,3,5);

//     all_sdf[0] = sdf_ellipsoid;

//     return min_lst(all_sdf, nb);
// }



RES_SDF scene_pingoo(VECTOR pts){
    int nb = 1;
    RES_SDF all_sdf[nb];

    VECTOR C_1 = {10,10,10};
    RES_SDF tete = SDF_Pingoo(pts, C_1, 3); 

    all_sdf[0] = tete;

    return min_lst_sdf(all_sdf, nb);
}



// float scene_5(vector pts){
//     int nb = 4;
//     float all_sdf[nb];
    
//     vector C_1 = {-3,0,0};
//     vector C_2 = {1,4,6};
//     vector C_3 = {2,-2,1};


//     float s_1 = SDF_sphere(pts, C_1,5);
//     float s_2 = SDF_sphere(pts, C_2,5);
//     float s_3 = SDF_sphere(pts, C_3,5);

//     vector C_1t = {-3,0,0};
//     vector C_2t = {1,4,6};
//     vector C_3t = {2,-2,1};

//     float sdf_1 = SDF_triangle(pts,C_1t,C_2t,C_3t);
//     // float sdf_1 = SDF_sphere(pts,C_2t,0.5);

//     // vector n = {0,0,1};
//     // vector m = {0,0,0};

//     // float sdf_2 = SDF_plan(pts,n,m);
//     // printf("%f \n",sdf_2);

//     float sdf_plan = SDF_plan(pts,(vector){16,26,-28},(vector){1,4,6});

//     all_sdf[0] = IntersectSDF(s_1,sdf_1);
//     all_sdf[1] = IntersectSDF(s_2,sdf_1);
//     all_sdf[2] = IntersectSDF(s_3,sdf_1);
//     all_sdf[3] = 100000;

//     return sdf_1;

//     return IntersectSDF(IntersectSDF(IntersectSDF(s_1,sdf_1),IntersectSDF(s_2,sdf_1)),IntersectSDF(s_3,sdf_1));
// }



// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
// RES_SDF SCENE_PRINCIPAL(vector pts){

//     return scene_sphere(pts);

//     // return SDF_pingouin_2(rotation_x(rotation_z(pts, -50),270),pts);
// }




