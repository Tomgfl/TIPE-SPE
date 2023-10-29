#include "vector.h"
#include "options.h"
#include "signed_distance_function.h"
#include <math.h>

// renvoie le vecteur normal a une surface (en un point proche d'une surface) a l'aide du gradient
vector vect_normal(coord pts){
    float dist = MIN_ALL_SDF(pts);

    float grad_x = MIN_ALL_SDF((coord){pts.x + EPSILON, pts.y, pts.z}) - dist;
    float grad_y = MIN_ALL_SDF((coord){pts.x, pts.y + EPSILON, pts.z}) - dist;
    float grad_z = MIN_ALL_SDF((coord){pts.x, pts.y, pts.z + EPSILON}) - dist;

    vector v = {grad_x, grad_y, grad_z};
    return v;
}



// Renvoie le produit vectoriel entre 2 vecteurs
vector prod_vect(vector v1, vector v2){
    vector v;
    v.x = v1.y*v2.z - v1.z*v2.y;
    v.y = v1.z*v2.x - v1.x*v2.z;
    v.z = v1.x*v2.y - v1.y*v2.x;

    return v;
}


float prod_scal(vector v1, vector v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}



// cree le vecteur entre 2 points
vector get_vec_2_pts(coord p_1, coord p_2){
    vector vec;
    vec.x = p_2.x - p_1.x;
    vec.y = p_2.y - p_1.y;
    vec.z = p_2.z - p_1.z;
    return vec;
}


// normalise un vecteur
vector normalise_vecteur(vector v){
    float l = sqrt (v.x*v.x + v.y*v.y + v.z*v.z);
    v.x = v.x / l;
    v.y = v.y / l;
    v.z = v.z / l;
    return v;
}


vector reflect (vector vi, vector vn){
    vi = normalise_vecteur(vi);
    vn = normalise_vecteur(vn);

    float ps = prod_scal(vi, vn);
    vector r;
    r.x = vi.x - 2.0*ps*vn.x;
    r.y = vi.y - 2.0*ps*vn.y;
    r.z = vi.z - 2.0*ps*vn.z;

    return r;
}