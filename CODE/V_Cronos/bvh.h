#ifndef BVH_H 
#define BVH_H

#include <stdbool.h>


#include "pingouin_sdf.h"
#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"
#include "options.h"
#include "objets.h"


#define MAX_OBJ_PER_LEAF 2  // Nombre de sdf max par feuille




BVHNode* buildBVH(OBJET* sdf_list, int sdf_count) ;
void splitOBJs(OBJET* sdf_list, int sdf_count, OBJET** left_sdfs, int* left_count, OBJET** right_sdfs, int* right_count, int depth) ;
float distBoule(vector p, BOULE box);
int compareByXPosition(const void* a, const void* b) ;
int compareByYPosition(const void* a, const void* b) ;
int compareByZPosition(const void* a, const void* b) ;
BOULE calculateBoundingBox(OBJET* sdf_list, int sdf_count) ;
void buildBVHRecursive(BVHNode* node, int currentDepth) ;
res_SDF traverseBVH(BVHNode* root, vector p, res_SDF dist) ;
void freeBVH (BVHNode* root) ;

#endif 