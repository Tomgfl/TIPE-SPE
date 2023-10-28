#ifndef SIGNED_DISTANCE_FUNCTION_H 
#define SIGNED_DISTANCE_FUNCTION_H


// type pour un point (x,y,z)
struct coord_s{
    float x, y, z;
};
typedef struct coord_s coord;

// vecteur 3d
struct vector_s{
    float x, y, z;
};
typedef struct vector_s vector;

// rayon
struct ray_s{
    coord origine;
    vector direction;
};
typedef struct ray_s ray;






// cree le vecteur entre 2 points
vector get_vec_2_pts(coord p_1, coord p_2);

// normalise un vecteur
vector normalise_vecteur (vector v);

// SDF
float SDF_sphere(coord pts, coord centre, float rayon);




#endif 