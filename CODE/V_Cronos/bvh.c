#include "bvh.h"

#include <stdlib.h>
#include <stdbool.h>



BVHNode* buildBVH(OBJET* obj_list, int obj_count) {
    BVHNode* root = (BVHNode*)malloc(sizeof(BVHNode));
    root->obj = obj_list;
    root->obj_count = obj_count;
    // Calculer la boîte englobante pour la racine en fonction des objets contenus
    root->box = calculateBoundingBox(obj_list, obj_count);

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



AABB calculateBoundingBox(OBJET* obj_list, int obj_count) {
    // Initialiser les coordonnées min et max avec des valeurs extrêmes
    float minX = INFINITY, minY = INFINITY, minZ = INFINITY;
    float maxX = -INFINITY, maxY = -INFINITY, maxZ = -INFINITY;

    // Parcourir tous les objets pour trouver les coordonnées min et max
    for (int i = 0; i < obj_count; ++i) {
        float x = obj_list[i].centre.x;
        float y = obj_list[i].centre.y;
        float z = obj_list[i].centre.z;

        // Mettre à jour les coordonnées min et max
        minX = fmin(minX, x - obj_list[i].rayon);
        minY = fmin(minY, y - obj_list[i].rayon);
        minZ = fmin(minZ, z - obj_list[i].rayon);

        maxX = fmax(maxX, x + obj_list[i].rayon);
        maxY = fmax(maxY, y + obj_list[i].rayon);
        maxZ = fmax(maxZ, z + obj_list[i].rayon);
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


void splitOBJs(OBJET* obj_list, int obj_count, OBJET** left_objs, int* left_count, OBJET** right_objs, int* right_count, int dep) {
    // Trier les objets en fonction de leur position sur l'axe x
    if (dep % 3 == 0){
        qsort(obj_list, obj_count, sizeof(OBJET), compareByXPosition);
    }   else if (dep % 3 == 1){
        qsort(obj_list, obj_count, sizeof(OBJET), compareByYPosition);
    }   else {
        qsort(obj_list, obj_count, sizeof(OBJET), compareByXPosition);
    }

    // Trouver l'indice de séparation pour diviser les objets en deux groupes
    int midpoint = obj_count / 2;

    // Assigner les objets aux groupes gauche et droit
    *left_objs = obj_list;
    *left_count = midpoint;

    *right_objs = obj_list + midpoint;
    *right_count = obj_count - midpoint;
}



// Fonction de comparaison pour qsort : compare les objets en fonction de leur position sur l'axe x
int compareByXPosition(const void* a, const void* b) {
    OBJET obj_a = *((OBJET*)a);
    OBJET obj_b = *((OBJET*)b);

    if (obj_a.centre.x < obj_b.centre.x) return -1;
    if (obj_a.centre.x > obj_b.centre.x) return 1;
    return 0;
}

// Fonction de comparaison pour qsort : compare les objets en fonction de leur position sur l'axe y
int compareByYPosition(const void* a, const void* b) {
    OBJET obj_a = *((OBJET*)a);
    OBJET obj_b = *((OBJET*)b);

    if (obj_a.centre.y < obj_b.centre.y) return -1;
    if (obj_a.centre.y > obj_b.centre.y) return 1;
    return 0;
}

// Fonction de comparaison pour qsort : compare les objets en fonction de leur position sur l'axe z
int compareByZPosition(const void* a, const void* b) {
    OBJET obj_a = *((OBJET*)a);
    OBJET obj_b = *((OBJET*)b);

    if (obj_a.centre.z < obj_b.centre.z) return -1;
    if (obj_a.centre.z > obj_b.centre.z) return 1;
    return 0;
}



void buildBVHRecursive(BVHNode* node, int currentDepth) {
    if (node->obj_count <= MAX_OBJ_PER_LEAF) {
        // Si le nombre d'objets est inférieur ou égal à un certain seuil ou si la profondeur maximale est atteinte,
        // considérez ce nœud comme une feuille et arrêtez la récursion
        node->left = NULL;
        node->right = NULL;
        return;
    }

    // Divisez les objets en deux groupes et créez les sous-arbres gauche et droit
    OBJET* left_objs;
    OBJET* right_objs;
    int left_count, right_count;

    splitOBJs(node->obj, node->obj_count, &left_objs, &left_count, &right_objs, &right_count, currentDepth);

    // Créer les sous-arbres gauche et droit
    node->left = (BVHNode*)malloc(sizeof(BVHNode));
    node->left->obj = left_objs;
    node->left->obj_count = left_count;
    node->left->box = calculateBoundingBox(left_objs, left_count);
    buildBVHRecursive(node->left, currentDepth + 1);

    node->right = (BVHNode*)malloc(sizeof(BVHNode));
    node->right->obj = right_objs;
    node->right->obj_count = right_count;
    node->right->box = calculateBoundingBox(right_objs, right_count);
    buildBVHRecursive(node->right, currentDepth + 1);
}



res_SDF traverseBVH(BVHNode* root, vector p, res_SDF dist) {
    res_SDF res;
    res = dist;
    if (root->left == NULL && root->right == NULL) {                    // Si c'est une feuille on retourne l'objet minimale
        res = min_sdf(res, SDF_Objet(p, min_lst_obj(root->obj, root->obj_count, p)));
    }   else {
        // Si ce n'est pas une feuille, il a un arbre gauche ET droit (il faut mettre MAX_OBJ_PER_LEAF >= 2)
        float d1 = distBoite(p, root->left->box);   // Distance Boite de gauche
        float d2 = distBoite(p, root->right->box);  // Distance Boite de droite
        if (d1<d2 && d1<res.dist) {
            res = traverseBVH(root->left, p, res);
            if (d2 < res.dist){
                res = traverseBVH(root->right, p, res);
            }
        }   else if (d2<d1 && d2<res.dist) {
            res = traverseBVH(root->right, p, res);
            if (d1 < res.dist){
                res = traverseBVH(root->left, p, res);
            }
        }
    }
    return res;
}


