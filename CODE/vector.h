#ifndef VECTOR_H 
#define VECTOR_H

// vecteur 3d
struct vector_s{
    float x, y, z;
};
typedef struct vector_s vector;


// type pour un point (x,y,z)
struct coord_s{
    float x, y, z;
};
typedef struct coord_s coord;


vector vect_normal(coord pts); // Renvoie le vecteur normale a une surface (en un point)
vector prod_vect(vector v1, vector v2); // renvoie le produit vectoriel
float prod_scal(vector v1, vector v2); // renvoie le produit scalaire
vector get_vec_2_pts(coord p_1, coord p_2); // cree le vecteur entre 2 points
vector normalise_vecteur (vector v); // normalise un vecteur
vector reflect (vector vi, vector vn); // fait la "reflexion" du vecteur incident par rapport au vecteur normal

#endif 