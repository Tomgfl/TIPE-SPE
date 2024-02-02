#include "scene.h"

extern float time_scene;

// --- SCENE --- //
res_SDF scene_sphere(vector pts){
    int nb = 1;
    res_SDF all_sdf[nb];

    vector C = {0,0,7};
    res_SDF sdf_sphere = SDF_sphere(pts, C, 2, c_orange);
    sdf_sphere = Disturb(pts, sdf_sphere);

    return sdf_sphere;

}

// --- SCENE #1 --- // Tous les objets
res_SDF scene_1(vector pts){
    int nb = 6;
    res_SDF all_sdf[nb];

    vector n_plan = {0, 0, 1};
    res_SDF sdf_plan = SDF_plan(pts, n_plan, (vector){0,0,-4}, c_gris);

    vector C_1 = {-10,10,0};
    res_SDF sdf_box = SDF_box(pts, C_1, 4,4,4, c_bleu);

    vector C_2 = {-10,10,10};
    res_SDF sdf_sphere = SDF_sphere(pts, C_2, 2, c_blanc);

    vector C_3 = {10,10,0};
    res_SDF sdf_tor = SDF_Tor(pts, C_3, 2, 1, c_bleu_berlin);
    sdf_tor = Disturb(pts, sdf_tor);

    vector C_4 = {0,10,10};
    res_SDF sdf_tri = SDF_triangle(pts, (vector){-3,10,8},(vector){3,10,10},(vector){0,10,13},c_vert);
    // res_SDF sdf_cylindre = SDF_cylindre(pts, C_4, 6, 1, c_bistre);

    vector C_5 = {0,10,0};
    res_SDF sdf_ell = SDF_Ellipsoid(pts, C_5, 3.2, 1.0, 1.6, c_orange);
    // res_SDF sdf_cone = SDF_Cone(pts, C_5, 6, 2, c_noir);


    all_sdf[0] = sdf_plan;
    all_sdf[1] = sdf_tor;
    all_sdf[2] = sdf_box;
    all_sdf[3] = sdf_tri;
    all_sdf[4] = sdf_ell;
    all_sdf[5] = sdf_sphere;

    return min_lst_sdf(all_sdf, nb);
}



res_SDF scene_effets(vector pts){
    int nb = 1;
    res_SDF all_sdf[nb];

    vector C_1 = {15,-2,12};
    res_SDF sphere_1 = SDF_sphere(pts, C_1, 4.0, c_orange);
    sphere_1 = Disturb(pts, sphere_1);

    all_sdf[0] = sphere_1;

    return min_lst_sdf(all_sdf, nb);
}

res_SDF banquise(vector pts){
    res_SDF res = SDF_pingouin(rotation_y(rotation_x(pts, 270),-60), pts);
    return res;
}



// video paysage


float coeff_i_j(int i,int j){
    double k;
    float u = 50*modf(i/3.1415, &k);
    float v = 50*modf(j/3.1415, &k);

    float a_i_j = modf(u*v*(u+v),&k)-1;

    return a_i_j;
}



float smoothstep(float a, float b, float x){
    // a < b
    float l = fmin(1,fmax(0,(x-a)/(b-a)));
    return l*l*(3-2*l);
}


float nurbs_paysage(float x, float z){
    int i = floorf(x);
    int j = floorf(z);

    float a = coeff_i_j(i,j);
    float b = coeff_i_j(i+1,j);
    float c = coeff_i_j(i,j+1);
    float d = coeff_i_j(i+1, j+1);

    float res = 
        a + 
        (b-a)*smoothstep(0,1,x-i) +
        (c-a)*smoothstep(0,1,z-j) + 
        (a-b-c+d)*smoothstep(0,1,x-i)*smoothstep(0,1,z-j);
    
    return res;

}

res_SDF paysage(vector pts){
    res_SDF res;
    res.c = c_orange;
    res.c = (color){floor(10*pts.x/MAX_TOTAL_LENGHT),floor(10*pts.y/MAX_TOTAL_LENGHT),floor(10*pts.z/MAX_TOTAL_LENGHT),1.0};
    
    if (pts.z < nurbs_paysage(pts.x, pts.y)){
        res.dist = 0.0;
        return res;
    }
    res.dist = 10*DIST_MIN;
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



res_SDF scene_pingoo(vector pts){
    int nb = 1;
    res_SDF all_sdf[nb];

    vector C_1 = {10,10,10};
    res_SDF tete = SDF_Pingoo(pts, C_1, 3); 

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
// res_SDF SCENE_PRINCIPAL(vector pts){

//     return scene_sphere(pts);

//     // return SDF_pingouin_2(rotation_x(rotation_z(pts, -50),270),pts);
// }




