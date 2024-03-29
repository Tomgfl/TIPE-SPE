#include "scene.h"
#include <stdio.h>
#include <stdlib.h>



extern float time_scene;



extern float time_scene;

// --- SCENE --- //
// res_SDF scene_sphere(vector pts){
//     int nb = 1;
//     res_SDF all_sdf[nb];

//     param_sphere* param2 = malloc(sizeof(param_sphere));
//     vector C = {0,0,7};
//     param2->centre = C;
//     param2->rayon = 2;
//     res_SDF sdf_sphere = SDF_sphere(pts, param2, c_orange);
//     // sdf_sphere = Disturb(pts, sdf_sphere);

//     return sdf_sphere;

// }

// --- SCENE #1 --- // Tous les objets
res_SDF scene_1(vector pts){
    int nb = 8;
    res_SDF all_sdf[nb];

    vector n_plan = {0, 0, 1};
    res_SDF sdf_plan = SDF_plan(pts, n_plan, (vector){0,0,-4}, c_gris);

    OBJET obj1 = BuildBox((vector){-10,10,0}, 4, 4, 4, c_bleu);
    res_SDF sdf_box = SDF_Objet(pts, obj1);
    FreeObj(obj1);

    OBJET obj2 = BuildSphere((vector){-10, 10, 10}, 2, c_blanc);
    res_SDF sdf_sphere = SDF_Objet(pts, obj2);
    FreeObj(obj2);

    OBJET obj3 = BuildTor((vector){10, 10, 0}, 2, 1, c_bleu_berlin);
    res_SDF sdf_tor = SDF_Objet(pts, obj3);
    FreeObj(obj3);

    OBJET obj4 = BuildSphere((vector){20 + 20*cos(time_scene/2), -20 + 20*sin(time_scene/2), 10 + 2*cos(time_scene/2)}, 3, c_rouge);
    OBJET obj5 = BuildSphere((vector){20 + 20*cos(time_scene/3), -20 + 20*sin(time_scene/3), 10 + 2*cos(time_scene/3)}, 3, c_rouge);
    OBJET obj6 = BuildSphere((vector){20 + 20*cos(time_scene/4), -20 + 20*sin(time_scene/4), 10 + 2*cos(time_scene/4)}, 3, c_rouge);
    OBJET obj7 = BuildSphere((vector){20 + 20*cos(time_scene/5), -20 + 20*sin(time_scene/5), 10 + 2*cos(time_scene/5)}, 3, c_rouge);
    res_SDF sdf_sph1 = SDF_Objet(pts, obj4);
    FreeObj(obj4);
    res_SDF sdf_sph2 = SDF_Objet(pts, obj5);
    FreeObj(obj5);
    res_SDF sdf_sph3 = SDF_Objet(pts, obj6);
    FreeObj(obj6);
    res_SDF sdf_sph4 = SDF_Objet(pts, obj7);
    FreeObj(obj7);


    // OBJET obj4 = BuildCylindre((vector){10, 10, 10}, 4, 2, c_rouge);
    // res_SDF sdf_cyl = SDF_Objet(pts, obj4);
    // FreeObj(obj4);

    // OBJET obj5 = BuildTriangle((vector){-3, 10, 8}, (vector){3,10,10}, (vector){0,10,13}, c_orange);
    // res_SDF sdf_tri = SDF_Objet(pts, obj5);
    // FreeObj(obj5);

    // OBJET obj6 = BuildEllipsoid((vector){0, 10, 0}, 2, 2.7, 3.5, c_vert);
    // res_SDF sdf_ell = SDF_Objet(pts, obj6);
    // sdf_tor = Disturb(pts, sdf_tor);

    // param_triangle* param4 = malloc(sizeof(param_triangle));
    // param4->a = (vector){-3,10,8};
    // param4->b = (vector){3,10,10};
    // param4->c = (vector){0,10,13};
    // res_SDF sdf_tri = SDF_triangle(pts, param4,c_vert);
    // // res_SDF sdf_cylindre = SDF_cylindre(pts, C_4, 6, 1, c_bistre);


    // param_ellipsoid* param5 = malloc(sizeof(param_ellipsoid));
    // param5->centre = (vector){0,10,0};
    // param5->a = 3.2;
    // param5->b = 1.0;
    // param5->c = 1.6;    
    // res_SDF sdf_ell = SDF_Ellipsoid(pts, param5, c_orange);
    // // res_SDF sdf_cone = SDF_Cone(pts, C_5, 6, 2, c_noir);

    all_sdf[0] = sdf_plan;
    all_sdf[1] = sdf_box;
    all_sdf[2] = sdf_sphere;
    all_sdf[3] = sdf_tor;
    all_sdf[4] = sdf_sph1;
    all_sdf[5] = sdf_sph2;
    all_sdf[6] = sdf_sph3;
    all_sdf[7] = sdf_sph4;
    // all_sdf[4] = sdf_cyl;
    // all_sdf[5] = sdf_tri;
    // all_sdf[6] = sdf_ell;
    return min_lst_sdf(all_sdf, nb);
}


BVHNode* scene1_bvh () {

    int nb = 3;
    OBJET all_obj[nb];
    all_obj[0] = BuildBox((vector){-10,10,0}, 4, 4, 4, c_bleu);
    all_obj[1] = BuildSphere((vector){-10, 10, 10}, 2, c_blanc);
    all_obj[2] = BuildTor((vector){10, 10, 0}, 2, 1, c_bleu_berlin);
    // all_obj[3] = BuildCylindre((vector){10, 10, 10}, 4, 2, c_rouge);
    // all_obj[4] = BuildTriangle((vector){-3, 10, 8}, (vector){3,10,10}, (vector){0,10,13}, c_orange);
    // all_obj[5] = BuildEllipsoid((vector){0, 10, 0}, 2, 2.7, 3.5, c_vert);

    BVHNode* root = buildBVH(all_obj, nb);

    return root;
}


BVHNode* TestBanquise () {
    int nb = 4;
    OBJET all_obj[nb];
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


BVHNode* SceneBouge () {
    int nb = 4;
    OBJET all_obj[nb];
    all_obj[0] = BuildSphere((vector){20 + 20*cos(time_scene/2), -20 + 20*sin(time_scene/2), 10 + 2*cos(time_scene/2)}, 3, c_rouge);
    all_obj[1] = BuildSphere((vector){20 + 20*cos(time_scene/3), -20 + 20*sin(time_scene/3), 10 + 2*cos(time_scene/3)}, 3, c_rouge);
    all_obj[2] = BuildSphere((vector){20 + 20*cos(time_scene/4), -20 + 20*sin(time_scene/4), 10 + 2*cos(time_scene/4)}, 3, c_rouge);
    all_obj[3] = BuildSphere((vector){20 + 20*cos(time_scene/5), -20 + 20*sin(time_scene/5), 10 + 2*cos(time_scene/5)}, 3, c_rouge);

    BVHNode* root = buildBVH(all_obj, nb);
    return root;

}





// res_SDF scene_effets(vector pts){
//     int nb = 1;
//     res_SDF all_sdf[nb];

//     vector C_1 = {15,-2,12};
//     res_SDF sphere_1 = SDF_sphere(pts, C_1, 4.0, c_orange);
//     sphere_1 = Disturb(pts, sphere_1);

//     all_sdf[0] = sphere_1;

//     return min_lst_sdf(all_sdf, nb);
// }

// res_SDF banquise(vector pts){
    
//     return SDF_pingouin(rotation_y(rotation_x(pts, 90), 35), pts);
// }



// video paysage


// float coeff_i_j(int i,int j){
//     double k;
//     float u = 50*modf(i/3.1415, &k);
//     float v = 50*modf(j/3.1415, &k);

//     float a_i_j = modf(u*v*(u+v),&k)-1;

//     return a_i_j;
// }



// float smoothstep(float a, float b, float x){
//     // a < b
//     float l = fmin(1,fmax(0,(x-a)/(b-a)));
//     return l*l*(3-2*l);
// }


// float nurbs_paysage(float x, float z){
//     int i = floorf(x);
//     int j = floorf(z);

//     float a = coeff_i_j(i,j);
//     float b = coeff_i_j(i+1,j);
//     float c = coeff_i_j(i,j+1);
//     float d = coeff_i_j(i+1, j+1);

//     float res = 
//         a + 
//         (b-a)*smoothstep(0,1,x-i) +
//         (c-a)*smoothstep(0,1,z-j) + 
//         (a-b-c+d)*smoothstep(0,1,x-i)*smoothstep(0,1,z-j);
    
//     return res;

// }

// res_SDF paysage(vector pts){
//     res_SDF res;
//     res.c = c_orange;
//     res.dist = nurbs_paysage(pts.x, pts.z);
//     return res;
// }






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






// // --- SCENE #4 --- // Test ellipsoid
// float scene_4(vector pts){
//     int nb = 1;
//     float all_sdf[nb];
//     vector C_1 = {-5,10,15};
//     float sdf_ellipsoid = SDF_Ellipsoid(rotation_z((vector){pts.x-C_1.x,pts.y-C_1.y,pts.z-C_1.z}, time_scene), (vector){0,0,0}, 2,3,5);
//     all_sdf[0] = sdf_ellipsoid;
//     return min_lst(all_sdf, nb);
// }



// res_SDF scene_pingoo(vector pts){
//     int nb = 1;
//     res_SDF all_sdf[nb];
//     vector C_1 = {10,10,10};
//     res_SDF tete = SDF_Pingoo(pts, C_1, 3); 
//     all_sdf[0] = tete;
//     return min_lst_sdf(all_sdf, nb);
// }



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
    res_SDF res = traverseBVH(scene, pts, (res_SDF){500,c_rouge});
    return res;
}


res_SDF SCENE_FIXE(vector pts){
    return scene_1(pts);
    // return SDF_pingouin_2(rotation_x(rotation_z(pts, -50),270),pts);
}
BVHNode* SCENE_MOUVANTE(){
    BVHNode* res = SceneBouge();
    return res;
}

