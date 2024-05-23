#include "bvh.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>



BVHNode* buildBVH(OBJET* obj_list, int obj_count) {
    BVHNode* root = (BVHNode*)malloc(sizeof(struct BVHNode_s));
    root->obj = obj_list;
    root->obj_count = obj_count;
    // Calculer la boîte englobante pour la racine en fonction des objets contenus
    root->box = calculateBoundingBox(obj_list, obj_count);

    // Appel récursif pour construire le BVH
    buildBVHRecursive(root, 0);

    return root;
}


float distBoule(vector p, BOULE box) {
    float dist = dist_2_pts(p, box.centre);
    return(dist - box.r);
}


BOULE calculateBoundingBox(OBJET* list, int obj_count) {
    // Si la liste d'objets est vide, retourner une sphère avec un rayon nul au centre de l'origine
    if (obj_count == 0) {
        BOULE bounding_sphere = {{0.0, 0.0, 0.0}, 0.0};
        return bounding_sphere;
    }

    // Initialiser les valeurs extrêmes pour le calcul des limites de la sphère englobante
    float min_x = list[0].centre.x - list[0].rayon , min_y = list[0].centre.y - list[0].rayon, min_z = list[0].centre.z - list[0].rayon;
    float max_x = list[0].centre.x + list[0].rayon , max_y = list[0].centre.y + list[0].rayon, max_z = list[0].centre.z + list[0].rayon;

    // Trouver les coordonnées minimales et maximales de tous les objets
    for (int i = 1; i < obj_count; ++i) {
        OBJET obj = list[i];
        // Mettre à jour les coordonnées minimales
        if (obj.centre.x - obj.rayon < min_x) min_x = obj.centre.x - obj.rayon;
        if (obj.centre.y - obj.rayon < min_y) min_y = obj.centre.y - obj.rayon;
        if (obj.centre.z - obj.rayon < min_z) min_z = obj.centre.z - obj.rayon;
        // Mettre à jour les coordonnées maximales
        if (obj.centre.x + obj.rayon > max_x) max_x = obj.centre.x + obj.rayon;
        if (obj.centre.y + obj.rayon > max_y) max_y = obj.centre.y + obj.rayon;
        if (obj.centre.z + obj.rayon > max_z) max_z = obj.centre.z + obj.rayon;
    }

    // Calculer le centre de la sphère englobante
    float center_x = (min_x + max_x) / 2.0f;
    float center_y = (min_y + max_y) / 2.0f;
    float center_z = (min_z + max_z) / 2.0f;

    // Calculer le rayon de la sphère englobante
    float radius = fmaxf(fmaxf(max_x - center_x, max_y - center_y), max_z - center_z);

    // Créer et retourner la sphère englobante calculée
    BOULE bounding_sphere = {{center_x, center_y, center_z}, radius};
    return bounding_sphere;
}


void splitOBJs(OBJET* obj_list, int obj_count, OBJET** left_objs, int* left_count, OBJET** right_objs, int* right_count, int dep) {
    // Trier les objets en fonction de leur position sur l'axe x
    if (dep % 3 == 0){
        qsort(obj_list, obj_count, sizeof(OBJET), compareByXPosition);
    }   else if (dep % 3 == 1){
        qsort(obj_list, obj_count, sizeof(OBJET), compareByYPosition);
    }   else {
        qsort(obj_list, obj_count, sizeof(OBJET), compareByZPosition);
    }

    // Trouver l'indice de séparation pour diviser les objets en deux groupes
    int midpoint = obj_count / 2;

    // Assigner les objets aux groupes gauche et droit
    *left_objs = malloc(midpoint* sizeof(OBJET));
    for (int i = 0; i < midpoint; i++){
        (*left_objs)[i] = obj_list[i];
    }
    *left_count = midpoint;

    *right_objs = malloc((obj_count - midpoint)* sizeof(OBJET));
    for (int i = 0; i < obj_count - midpoint; i++){
        (*right_objs)[i] = obj_list[midpoint + i];
    }    
    *right_count = obj_count - midpoint;
}


// Fonction de comparaison pour qsort : compare les objets en fonction de leur position sur l'axe x
int compareByXPosition(const void* a, const void* b) {
    OBJET obj_a = *((OBJET*)a);
    OBJET obj_b = *((OBJET*)b);

    if (obj_a.centre.x < obj_b.centre.x) return -1;
    return 1;
}

// Fonction de comparaison pour qsort : compare les objets en fonction de leur position sur l'axe y
int compareByYPosition(const void* a, const void* b) {
    OBJET obj_a = *((OBJET*)a);
    OBJET obj_b = *((OBJET*)b);

    if (obj_a.centre.y < obj_b.centre.y) return -1;
    return 1;
}

// Fonction de comparaison pour qsort : compare les objets en fonction de leur position sur l'axe z
int compareByZPosition(const void* a, const void* b) {
    OBJET obj_a = *((OBJET*)a);
    OBJET obj_b = *((OBJET*)b);

    if (obj_a.centre.z < obj_b.centre.z) return -1;
    return 1;
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
        float d1 = FLT_MAX ; float d2 = FLT_MAX; 
        if (root->left != NULL) { d1 = distBoule(p, root->left->box); }   // Distance Boite de gauche
        if (root->right != NULL) { d2 = distBoule(p, root->right->box); }  // Distance Boite de droite
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




// Function to merge a list of BVH trees into a single BVH
BVHNode* MergeBVH(BVHNode** bvh_list, int bvh_count) {
    
    int k = 0;
    for (int i = 0; i<bvh_count; i++){
        k = k + bvh_list[i]->obj_count;
    }

    int l = 0;
    OBJET* objs = malloc(k*sizeof(OBJET));
    for (int i = 0; i<bvh_count; i++){
        for (int j=0; j<bvh_list[i]->obj_count; j++){
            objs[j+l] = bvh_list[i]->obj[j];
        }
        l += bvh_list[i]->obj_count;
    }
    for (int i = 0; i<bvh_count; i++){
        FreeBranche(bvh_list[i]);
    } 

    BVHNode* root = buildBVH(objs, k);
    // free(bvh_list);
    return root;
}

void FreeBranche(BVHNode* root) {
    if (root == NULL) {
        return;
    }   
    FreeBranche(root->left);
    FreeBranche(root->right);
    free(root->obj);
    free(root);
}







void freeBVHAux(BVHNode* node){
    if (node == NULL) {
        return;
    }
    // Libérer la mémoire des sous-arbres gauche et droit
    freeBVHAux(node->left);
    freeBVHAux(node->right);
    free(node->obj);
    free(node);
}

void freeBVH(BVHNode* node) {
    if (node == NULL) {
        return;
    }
    // Libérer la mémoire des sous-arbres gauche et droit
    freeBVHAux(node->left);
    freeBVHAux(node->right);

    // Libérer la mémoire des objets
    if (node->obj_count > 0 && node->obj != NULL) {
        FreeObjList(node->obj, node->obj_count);
    }
    free(node);
}



