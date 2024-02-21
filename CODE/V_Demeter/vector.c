#include "vector.h"




// renvoie le vecteur normal a une surface (en un point proche d'une surface) a l'aide du gradient
VECTOR vect_normal(VECTOR pts, RES_SDF(*scene_actuelle)(VECTOR)){
    float dist = scene_actuelle(pts).dist;

    // float grad_x = SCENE_PRINCIPAL((vector){pts.x + EPSILON, pts.y, pts.z}) - dist;
    // float grad_y = SCENE_PRINCIPAL((vector){pts.x, pts.y + EPSILON, pts.z}) - dist;
    // float grad_z = SCENE_PRINCIPAL((vector){pts.x, pts.y, pts.z + EPSILON}) - dist;

    float grad_x = scene_actuelle(v_add(pts, (VECTOR){EPSILON,0,0})).dist - dist;
    float grad_y = scene_actuelle(v_add(pts, (VECTOR){0,EPSILON,0})).dist - dist;
    float grad_z = scene_actuelle(v_add(pts, (VECTOR){0,0,EPSILON})).dist - dist;

    VECTOR v = {grad_x, grad_y, grad_z};
    return normalise_vecteur(v);
}



// Renvoie le produit vectoriel entre 2 vecteurs
VECTOR prod_vect(VECTOR v1, VECTOR v2){
    VECTOR v;
    v.x = v1.y*v2.z - v1.z*v2.y;
    v.y = v1.z*v2.x - v1.x*v2.z;
    v.z = v1.x*v2.y - v1.y*v2.x;

    return v;
}


float prod_scal(VECTOR v1, VECTOR v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}




// cree le vecteur entre 2 points
VECTOR get_vec_2_pts(VECTOR p1, VECTOR p2){
    VECTOR vec;
    vec.x = p2.x - p1.x;
    vec.y = p2.y - p1.y;
    vec.z = p2.z - p1.z;
    return vec;
}


// normalise un vecteur
VECTOR normalise_vecteur(VECTOR v){
    float l = sqrt (v.x*v.x + v.y*v.y + v.z*v.z);
    v.x = v.x / l;
    v.y = v.y / l;
    v.z = v.z / l;
    return v;
}


VECTOR reflect (VECTOR vi, VECTOR vn){
    vi = normalise_vecteur(vi);
    vn = normalise_vecteur(vn);

    float ps = prod_scal(vi, vn);
    VECTOR r;
    r.x = vi.x - 2.0*ps*vn.x;
    r.y = vi.y - 2.0*ps*vn.y;
    r.z = vi.z - 2.0*ps*vn.z;

    return r;
}



float dist_2_pts(VECTOR p1, VECTOR p2){
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z) );
}


VECTOR v_add(VECTOR v1, VECTOR v2){
    return (VECTOR){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

VECTOR v_sub(VECTOR v1, VECTOR v2){
    return (VECTOR){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

VECTOR v_mult_scal(VECTOR v, float a){
    return (VECTOR){a*v.x,a*v.y,a*v.z};
}

float norm_vector(VECTOR v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); 
}