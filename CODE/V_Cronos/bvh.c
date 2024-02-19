#include "bvh.h"

#include <stdlib.h>
#include <stdbool.h>



BVHNode* buildBVH(res_SDF* sdf_list, int sdf_count) {
    BVHNode* root = (BVHNode*)malloc(sizeof(BVHNode));
    root->sdf = sdf_list;
    root->sdf_count = sdf_count;
    // Calculer la boîte englobante pour la racine en fonction des SDF contenus
    root->box = calculateBoundingBox(sdf_list, sdf_count);

    // Appel récursif pour construire le BVH
    buildBVHRecursive(root, 0);

    return root;
}


float distBoite(vector p, AABB box) {
    float x = MIN(fabs(box.minX-p.x), fabs(box.maxX-p.x));
    float y = MIN(fabs(box.minY-p.y), fabs(box.maxY-p.y));
    float z = MIN(fabs(box.minZ-p.z), fabs(box.maxZ-p.z));
    if (p.x > box.minX && p.x < box.maxX && p.y > box.minY && p.y < box.maxY && p.z > box.minZ && p.z < box.maxZ) {
        return -sqrt(x*x + y*y + z*z);
    }   else {
        if (p.x > box.minX && p.x < box.maxX) {
            if (p.y > box.minY && p.y < box.maxY) {
                return z;
            }   else if (p.z > box.minZ && p.z < box.maxZ) {
                return y;
            }   else {
                return sqrt(y*y + z*z);
            }
        }   else if (p.y > box.minY && p.y < box.maxY) {
            if (p.z > box.minZ && p.z < box.maxZ) {
                return x;
            }   else {
                return sqrt(x*x + z*z);
            }
        }   else if (p.z > box.minZ && p.z < box.maxZ){
            return sqrt(x*x + y*y);
        }   else {
            return (x*x + y*y + z*z);
        }
    }
}



AABB calculateBoundingBox(res_SDF* sdf_list, int sdf_count) {
    // Initialiser les coordonnées min et max avec des valeurs extrêmes
    float minX = INFINITY, minY = INFINITY, minZ = INFINITY;
    float maxX = -INFINITY, maxY = -INFINITY, maxZ = -INFINITY;

    // Parcourir tous les SDF pour trouver les coordonnées min et max
    for (int i = 0; i < sdf_count; ++i) {
        float x = sdf_list[i].centre.x;
        float y = sdf_list[i].centre.y;
        float z = sdf_list[i].centre.z;

        // Mettre à jour les coordonnées min et max
        minX = fmin(minX, x - sdf_list[i].rayon);
        minY = fmin(minY, y - sdf_list[i].rayon);
        minZ = fmin(minZ, z - sdf_list[i].rayon);

        maxX = fmax(maxX, x + sdf_list[i].rayon);
        maxY = fmax(maxY, y + sdf_list[i].rayon);
        maxZ = fmax(maxZ, z + sdf_list[i].rayon);
    }

    // Créer et retourner la boîte englobante
    AABB box;
    box.minX = minX;
    box.minY = minY;
    box.minZ = minZ;
    box.maxX = maxX;
    box.maxY = maxY;
    box.maxZ = maxZ;

    return box;
}


void splitSDFs(res_SDF* sdf_list, int sdf_count, res_SDF** left_sdfs, int* left_count, res_SDF** right_sdfs, int* right_count) {
    // Trier les SDF en fonction de leur position sur l'axe x
    qsort(sdf_list, sdf_count, sizeof(res_SDF), compareByXPosition);

    // Trouver l'indice de séparation pour diviser les SDF en deux groupes
    int midpoint = sdf_count / 2;

    // Assigner les SDF aux groupes gauche et droit
    *left_sdfs = sdf_list;
    *left_count = midpoint;

    *right_sdfs = sdf_list + midpoint;
    *right_count = sdf_count - midpoint;
}



// Fonction de comparaison pour qsort : compare les SDF en fonction de leur position sur l'axe x
int compareByXPosition(const void* a, const void* b) {
    res_SDF sdf_a = *((res_SDF*)a);
    res_SDF sdf_b = *((res_SDF*)b);

    if (sdf_a.centre.x < sdf_b.centre.x) return -1;
    if (sdf_a.centre.x > sdf_b.centre.x) return 1;
    return 0;
}



void buildBVHRecursive(BVHNode* node, int currentDepth) {
    if (node->sdf_count <= MAX_SDF_PER_LEAF) {
        // Si le nombre de SDF est inférieur ou égal à un certain seuil ou si la profondeur maximale est atteinte,
        // considérez ce nœud comme une feuille et arrêtez la récursion
        node->left = NULL;
        node->right = NULL;
        return;
    }

    // Divisez les SDF en deux groupes et créez les sous-arbres gauche et droit
    res_SDF* left_sdfs;
    res_SDF* right_sdfs;
    int left_count, right_count;

    splitSDFs(node->sdf, node->sdf_count, &left_sdfs, &left_count, &right_sdfs, &right_count);

    // Créer les sous-arbres gauche et droit
    node->left = (BVHNode*)malloc(sizeof(BVHNode));
    node->left->sdf = left_sdfs;
    node->left->sdf_count = left_count;
    node->left->box = calculateBoundingBox(left_sdfs, left_count);
    buildBVHRecursive(node->left, currentDepth + 1);

    node->right = (BVHNode*)malloc(sizeof(BVHNode));
    node->right->sdf = right_sdfs;
    node->right->sdf_count = right_count;
    node->right->box = calculateBoundingBox(right_sdfs, right_count);
    buildBVHRecursive(node->right, currentDepth + 1);
}



float traverseBVH(BVHNode* root, vector p, float dist) {
    float res = dist;
    if (root->left == NULL && root->right == NULL) {                    // Si c'est une feuille on retourne la sdf minimale
        res = MIN(res, min_lst_sdf(root->sdf, root->sdf_count).dist);
    }   else {
        // Si ce n'est pas une feuille, il a un arbre gauche ET droit (il faut mettre MAX_SDF_PER_LEAF >= 2)
        float d1 = distBoite(p, root->left->box);   // Distance Boite de gauche
        float d2 = distBoite(p, root->right->box);  // Distance Boite de droite
        if (d1<d2 && d1<res) {
            res = traverseBVH(root->left, p, res);
            if (d2 < res){
                res = traverseBVH(root->right, p, res);
            }
        }   else if (d2<d1 && d2<res) {
            res = traverseBVH(root->right, p, res);
            if (d1 < res){
                res = traverseBVH(root->left, p, res);
            }
        }
    }
    return res;
}


