#ifndef VECTOR_H 
#define VECTOR_H

#include "options.h"
// #include "signed_distance_function.h"
// #include "scene.h"
#include <math.h>






RES_SDF SCENE_PRINCIPAL(VECTOR p);

VECTOR vect_normal(VECTOR pts, RES_SDF(*scene_act)(VECTOR)); // Renvoie le vecteur normale a une surface (en un point)
VECTOR prod_vect(VECTOR v1, VECTOR v2); // renvoie le produit vectoriel
float prod_scal(VECTOR v1, VECTOR v2); // renvoie le produit scalaire
VECTOR get_vec_2_pts(VECTOR p1, VECTOR p2); // cree le vecteur entre 2 points
VECTOR normalise_vecteur (VECTOR v); // normalise un vecteur
VECTOR reflect (VECTOR vi, VECTOR vn); // fait la "reflexion" du vecteur incident par rapport au vecteur normal
float dist_2_pts(VECTOR p1, VECTOR p2); // renvoie la distance entre 2 points
VECTOR v_add(VECTOR v1, VECTOR v2);
VECTOR v_sub(VECTOR v1, VECTOR v2);
VECTOR v_mult_scal(VECTOR v, float a);
float norm_vector(VECTOR v);
#endif 