#include <math.h>

#include "signed_distance_function.h"







vector get_vec_2_pts(coord p_1, coord p_2){
    vector vec;
    vec.x = p_2.x - p_1.x;
    vec.y = p_2.y - p_1.y;
    vec.z = p_2.z - p_1.z;
    return vec;
}


vector normalise_vecteur(vector v){
    float l = sqrt (v.x*v.x + v.y*v.y + v.z*v.z);
    v.x = v.x / l;
    v.y = v.y / l;
    v.z = v.z / l;
    return v;
}



float SDF_sphere(coord pts, coord centre, float rayon){
    float distance = sqrt( (pts.x - centre.x)*(pts.x - centre.x) + (pts.y - centre.y)*(pts.y - centre.y) + (pts.z - centre.z)*(pts.z - centre.z) );
    return distance - rayon;
}

