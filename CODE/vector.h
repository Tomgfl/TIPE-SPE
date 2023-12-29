#ifndef VECTOR_H 
#define VECTOR_H

#include "options.h"
// #include "signed_distance_function.h"
// #include "scene.h"
#include <math.h>

// vecteur 3d
struct vector_s{
    float x, y, z;
};
typedef struct vector_s vector;




float SCENE_PRINCIPAL(vector p);

vector vect_normal(vector pts); // Renvoie le vecteur normale a une surface (en un point)
vector prod_vect(vector v1, vector v2); // renvoie le produit vectoriel
float prod_scal(vector v1, vector v2); // renvoie le produit scalaire
vector get_vec_2_pts(vector p1, vector p2); // cree le vecteur entre 2 points
vector normalise_vecteur (vector v); // normalise un vecteur
vector reflect (vector vi, vector vn); // fait la "reflexion" du vecteur incident par rapport au vecteur normal
float dist_2_pts(vector p1, vector p2); // renvoie la distance entre 2 points
vector v_add(vector v1, vector v2);
vector v_sub(vector v1, vector v2);
vector v_mult_scal(vector v, float a);
float norm_vector(vector v);
#endif 