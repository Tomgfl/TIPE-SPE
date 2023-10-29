#include <math.h>

#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"







float SDF_sphere(coord pts, coord centre, float rayon){
    float distance = sqrt( (pts.x - centre.x)*(pts.x - centre.x) + (pts.y - centre.y)*(pts.y - centre.y) + (pts.z - centre.z)*(pts.z - centre.z) );
    return distance - rayon;
}


float SDF_tor(coord p, float g_rayon, float p_rayon){
    float distanceToCenter = sqrt(p.x * p.x + p.y * p.y);
    float sdf = sqrt(distanceToCenter * distanceToCenter + p.z * p.z) - g_rayon;
    return sdf - p_rayon;
}





// --- SCENE --- //

// renvoie la surface la plus proche (ie c'est toutes les SDF de la scene)
float MIN_ALL_SDF(coord pts){
    float all_sdf[3];

    coord R_1 = {0.0, 7.0, 1.0}; float r_1 = 1.0; // caracteristique d'une sphere
    coord R_2 = {1.5, 8.0, 0.5}; float r_2 = 0.5;
    coord R_3 = {-2.0, 9.0, 2.0}; float r_3 = 1.0;
    

    float sdf_1 = SDF_sphere(pts, R_1, r_1);
    float sdf_2 = SDF_sphere(pts, R_2, r_2);
    float sdf_3 = SDF_sphere(pts, R_3, r_3);
    
    
    all_sdf[0] = sdf_1;
    all_sdf[1] = sdf_2;
    all_sdf[2] = sdf_3;


    return min_lst(all_sdf, 3);
}