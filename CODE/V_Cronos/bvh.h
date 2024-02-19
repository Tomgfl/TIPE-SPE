#ifndef BVH_H 
#define BVH_H

#include <stdbool.h>


#include "pingouin_sdf.h"
#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"
#include "options.h"

#define MAX_SDF_PER_LEAF 10
#define MAX_DEPTH 15 // Définissez ici la profondeur maximale souhaitée


typedef struct {
    float minX, minY, minZ; // Coin inférieur de la boîte
    float maxX, maxY, maxZ; // Coin supérieur de la boîte
} AABB;

typedef struct BVHNode {
    AABB box; // Axis-Aligned Bounding Box (Boîte englobante alignée sur les axes)
    struct BVHNode* left;
    struct BVHNode* right;
    res_SDF* sdf; // Pointeur vers le SDF (ou un tableau de SDF) contenu dans ce nœud
    int sdf_count; // Nombre de SDF contenu dans ce nœud
} BVHNode;

BVHNode* buildBVH(res_SDF* sdf_list, int sdf_count) ;
void splitSDFs(res_SDF* sdf_list, int sdf_count, res_SDF** left_sdfs, int* left_count, res_SDF** right_sdfs, int* right_count) ;
float distBoite(vector p, AABB box);
int compareByXPosition(const void* a, const void* b) ;
AABB calculateBoundingBox(res_SDF* sdf_list, int sdf_count) ;
void buildBVHRecursive(BVHNode* node, int currentDepth) ;
float traverseBVH(BVHNode* root, vector p, float dist) ;

#endif 