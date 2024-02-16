#ifndef BVH_H 
#define BVH_H

#include "pingouin_sdf.h"
#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"


// Structure de sphère englobante
struct bounding_sphere_s {
    vector center;
    float radius;
};
typedef struct bounding_sphere_s bounding_sphere;


struct BVH_node_s {
    bounding_sphere bounding_box;   // Sphère englobante
    res_SDF object;                 // SDF à l'intérieur
    struct BVH_node_s* g;           // Sous-arbre gauche
    struct BVH_node_s* d;           // Sous-arbre droit
};
typedef struct BVH_node_s BVH_node;


BVH_node* create_BVH_node(res_SDF object);
BVH_node* build_BVH(res_SDF* objects, int num_objects);


