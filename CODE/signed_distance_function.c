#include <math.h>

#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))







float SDF_sphere(coord p, coord centre, float rayon){
    float distance = sqrt( (p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y) + (p.z - centre.z)*(p.z - centre.z) );
    return distance - rayon;
}


float SDF_Tor(coord p, coord centre, float R, float r) {
    float distance_xy = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - R;
    return sqrt(distance_xy*distance_xy + (p.z - centre.z)*(p.z - centre.z)) - r;
}


float SDF_box(coord p, coord centre, float L, float l, float h){
    float dist;
    float d[3];
    d[0] = fabs(p.x - centre.x) - L/2.0;
    d[1] = fabs(p.y - centre.y) - l/2.0;
    d[2] = fabs(p.z - centre.z) - h/2.0;

    float dist_int = fmax(fmax(d[0],d[1]),d[2]);
    float dist_ext = sqrt(fmax(dist_int, 0.0));

    if (dist_int > 0){
        return dist_int;
    }   else{
        return dist_ext;
    }
}


float SDF_plan(coord p, vector n, float h){
    vector v = {p.x, p.y, p.z};
    return prod_scal(v,n) + h;
}





// --- SCENE --- //

// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
float MIN_ALL_SDF(coord pts){
    float all_sdf[3];

    //coord R_1 = {0.0, 7.0, 1.0}; float r_1 = 1.0; // caracteristique d'une sphere
    //coord R_2 = {1.5, 8.0, 0.5}; float r_2 = 0.5;
    coord R_3 = {0.0, 9.0, 2.0}; float r_3 = 1.5;
    //coord C_1 = {-2.0, 7.0, 2.0}; float L_1 = 3.0; float l_1 = 1.0; float h_1 = 0.3;
    coord T_1 = {0.0, 9.0, 2.0}; float Rt = 3; float rt = 0.2;
    vector n = {0.0, 0.0, 1.0};

    //float sdf_1 = SDF_sphere(pts, R_1, r_1);
    //float sdf_2 = SDF_sphere(pts, R_2, r_2);
    float sdf_3 = SDF_sphere(pts, R_3, r_3);
    //float sdf_4 = SDF_box(pts, C_1, L_1, l_1, h_1);
    float sdf_5 = SDF_Tor(pts, T_1, Rt, rt);    
    float sdf_6 = SDF_plan(pts, n, 0.0);
    
    all_sdf[0] = sdf_3;
    all_sdf[1] = sdf_5;
    all_sdf[2] = sdf_6;
    //all_sdf[2] = sdf_3;
    //all_sdf[3] = sdf_4;*/

    return min_lst(all_sdf, 3);
}