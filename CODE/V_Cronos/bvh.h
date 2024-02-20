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


typedef struct {
    float minX, minY, minZ; // Coin inférieur de la boîte
    float maxX, maxY, maxZ; // Coin supérieur de la boîte
} AABB;

typedef struct BVHNode {
    AABB box; // Axis-Aligned Bounding Box (Boîte englobante alignée sur les axes)
    struct BVHNode* left;
    struct BVHNode* right;
    OBJET* obj; // Pointeur vers l'objet (ou un tableau d'objets) contenu dans ce nœud
    int obj_count; // Nombre d'objets contenu dans ce nœud
} BVHNode;

BVHNode* buildBVH(OBJET* sdf_list, int sdf_count) ;
void splitOBJs(OBJET* sdf_list, int sdf_count, OBJET** left_sdfs, int* left_count, OBJET** right_sdfs, int* right_count, int depth) ;
float distBoite(vector p, AABB box);
int compareByXPosition(const void* a, const void* b) ;
int compareByYPosition(const void* a, const void* b) ;
int compareByZPosition(const void* a, const void* b) ;
AABB calculateBoundingBox(OBJET* sdf_list, int sdf_count) ;
void buildBVHRecursive(BVHNode* node, int currentDepth) ;
float traverseBVH(BVHNode* root, vector p, float dist) ;

#endif 