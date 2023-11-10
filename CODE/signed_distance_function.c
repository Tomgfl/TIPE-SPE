#include <math.h>
#include <stdio.h>

#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))







// float SDF_sphere(coord p, coord centre, float rayon){
//     //printf("%f\n",fmodf(p.x,1.0));
//     float distance = sqrt( (fmodf(p.x,1.0) - centre.x)*(fmodf(p.x,1.0) - centre.x) + (fmodf(p.y,1.0) - centre.y)*(fmodf(p.y,1.0) - centre.y) + (fmodf(p.z,1.0) - centre.z)*(fmodf(p.z,1.0) - centre.z) );
//     return distance - rayon;
// }

float SDF_sphere(coord p, coord centre, float rayon){
    float distance = sqrt( (p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y) + (p.z - centre.z)*(p.z - centre.z) );
    return distance - rayon;
}


float mult_objects(coord pos) {
    // translate
    // float iTime = 1.0;
    
    // pos.x += 0.0;
    // pos.y += 0.0;
    // pos.z += 0.0;

    coord modResult;
    // modResult.x = fmodf(pos.x, 2.0);
    modResult.y = fmodf(pos.y, 2.0);
    modResult.x = fmodf(pos.x, 2.0);
    // modResult.y = pos.y;
    // modResult.z = fmodf(pos.z, 2.0);
    modResult.z = pos.z;

    //float d1 = sqrt((modResult.x - 1.0) * (modResult.x - 1.0) + (modResult.y - 1.0) * (modResult.y - 1.0) + (modResult.z - 1.0) * (modResult.z - 1.0)) - 0.54321;
    // float d1 = SDF_box(modResult, (coord){1.0,1.0,1.0}, 0.5,0.5,0.5);
    float d1 = SDF_Tor(modResult, (coord){1.0,1.0,-1}, 0.5, 0.3);
    return d1;
}

float fractal_1_test(coord z) {
    coord a1 = {1.0, 1.0, 1.0};
    coord a2 = {-1.0, -1.0, 1.0};
    coord a3 = {1.0, -1.0, -1.0};
    coord a4 = {-1.0, 1.0, -1.0};
    coord c;
    int n = 0;
    float dist, d;
    int Iterations = 15;
    float Scale = 2.0;

    while (n < Iterations) {
        c = a1;
        dist = sqrt(pow(z.x - a1.x, 2) + pow(z.y - a1.y, 2) + pow(z.z - a1.z, 2));
        d = sqrt(pow(z.x - a2.x, 2) + pow(z.y - a2.y, 2) + pow(z.z - a2.z, 2));
        if (d < dist) {
            c = a2;
            dist = d;
        }
        d = sqrt(pow(z.x - a3.x, 2) + pow(z.y - a3.y, 2) + pow(z.z - a3.z, 2));
        if (d < dist) {
            c = a3;
            dist = d;
        }
        d = sqrt(pow(z.x - a4.x, 2) + pow(z.y - a4.y, 2) + pow(z.z - a4.z, 2));
        if (d < dist) {
            c = a4;
            dist = d;
        }

        z.x = Scale * z.x - c.x * (Scale - 1.0);
        z.y = Scale * z.y - c.y * (Scale - 1.0);
        z.z = Scale * z.z - c.z * (Scale - 1.0);
        n++;
    }

    return sqrt(pow(z.x, 2) + pow(z.y, 2) + pow(z.z, 2)) * pow(Scale, -n);
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


// renvoie le produit entre la matrice de rotation Rx et le vec v
coord rotation_x (coord v, float angle){// angle en rad
    return (coord){v.x, v.y*cos(angle) - v.z*sin(angle), v.y*sin(angle) + v.z*cos(angle)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
coord rotation_y (coord v, float angle){// angle en rad
    return (coord){v.x*cos(angle) + v.z*sin(angle), v.y, v.z*cos(angle) - v.x*sin(angle)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
coord rotation_z (coord v, float angle){// angle en rad
    return (coord){};
}





// --- SCENE --- //

// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
float MIN_ALL_SDF(coord pts){
    int nb = 4;
    float all_sdf[nb];

    //coord R_1 = {0.0, 7.0, 1.0}; float r_1 = 1.0; // caracteristique d'une sphere
    //coord R_2 = {1.5, 8.0, 0.5}; float r_2 = 0.5;
    coord R_3 = {0.0, 9.0, 2.5}; float r_3 = 1.5;
    //coord C_1 = {-2.0, 7.0, 2.0}; float L_1 = 3.0; float l_1 = 1.0; float h_1 = 0.3;
    coord T_1 = {0.0, 9.0, 2.5}; float Rt = 3; float rt = 0.2;
    coord R_4 = {6, 10, 2};
    coord R_5 = {-4, 6, 1};
    vector n = {0.0, 0.0, 1.0};

    //float sdf_1 = SDF_sphere(pts, R_1, r_1);
    //float sdf_2 = SDF_sphere(pts, R_2, r_2);
    float sdf_3 = SDF_sphere(pts, R_3, r_3);
    //float sdf_4 = SDF_box(pts, C_1, L_1, l_1, h_1);
    float sdf_5 = SDF_Tor(rotation_y(pts,2*3.14), T_1, Rt, rt);    
    float sdf_6 = SDF_plan(pts, n, 0.0);

    float sdf_7 = SDF_box(pts, R_4, 2, 3, 1);

    float sdf_8 = SDF_box(pts,R_5, 1, 1, 1);
    
    // float sdf_8 = mult_objects(pts);
    // all_sdf[0] = sdf_8;
    // all_sdf[0] = sdf_6;
    all_sdf[0] = sdf_3;
    all_sdf[1] = sdf_5;
    all_sdf[2] = sdf_7;
    all_sdf[3] = sdf_8;

    // all_sdf[0] = sdf_3;
    ////all_sdf[1] = sdf_5;
    ////all_sdf[2] = sdf_6;

    // all_sdf[0] = mult_objects(pts);
    // all_sdf[0] = sdf_3;
    // all_sdf[0] = fractal_1_test(pts);



    //all_sdf[2] = sdf_3;
    //all_sdf[3] = sdf_4;*/

    return min_lst(all_sdf, nb);
}