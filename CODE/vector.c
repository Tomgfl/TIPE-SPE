#include "vector.h"
#include "options.h"
#include "signed_distance_function.h"
#include "scene.h"
#include <math.h>




// renvoie le vecteur normal a une surface (en un point proche d'une surface) a l'aide du gradient
vector vect_normal(coord pts){
    float dist = SCENE_PRINCIPAL(pts);

    float grad_x = SCENE_PRINCIPAL((coord){pts.x + EPSILON, pts.y, pts.z}) - dist;
    float grad_y = SCENE_PRINCIPAL((coord){pts.x, pts.y + EPSILON, pts.z}) - dist;
    float grad_z = SCENE_PRINCIPAL((coord){pts.x, pts.y, pts.z + EPSILON}) - dist;

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
vector get_vec_2_pts(coord p1, coord p2){
    vector vec;
    vec.x = p2.x - p1.x;
    vec.y = p2.y - p1.y;
    vec.z = p2.z - p1.z;
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



float dist_2_pts(coord p1, coord p2){
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z) );
}