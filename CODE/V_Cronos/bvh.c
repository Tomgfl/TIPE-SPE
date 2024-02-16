#include "bvh.h"



// Alloue la mémoire à un BVH
BVHNode* build_bvh(vector c, float r) {
    BVHNode *node = malloc(sizeof(BVHNode));
    node->centre = c;
    node->rayon = r;
    node->g = NULL;
    node->d = NULL;
    node->object = NULL;
    return node;
}


// Libère la mémoire de l'arbre BVH
void free_bvh(BVHNode *node) {
    if (node == NULL) return;
    free_bvh(node->g);
    free_bvh(node->d);
    free(node);
}


// Insertion des SDF dans l'arbre
void insert_sdf_result(BVHNode *root, vector* c, float r, res_SDF* sdf_result) {
    // Vérifier si l'arbre est vide
    if (root == NULL) {
        // Créer un nouveau nœud racine avec le résultat SDF
        root = build_bvh(c,r);
        root->object = sdf_result;
        // Mise à jour de la sphère englobante de la racine
        root->centre = c;
        root->rayon = r;
        return;
    }  
    


}
