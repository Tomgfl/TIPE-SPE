#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "dessin_fct.h"
#include "options.h"
#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"
#include "light.h"
#include "scene.h"
#include "ray_marching.h"
#include "bvh.h"
#include "objets.h"

float time_scene = 0;
stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};


int main(){

    // int nb = 4;
    // OBJET* all_obj = malloc(nb*sizeof(OBJET));
    // all_obj[0] = BuildBox((vector){0,10,-10}, 500, 500, 20, c_blanc);
    // all_obj[1] = BuildSphere((vector){10, 70, 5}, 20, c_iceberg);
    // all_obj[2] = BuildRotY(BuildTor((vector){10, 40, 10}, 7, 2, c_iceberg), 2);
    // all_obj[3] = BuildSphere((vector){10, 40, 10}, 2, c_rouge);
    // BVHNode* root1 = buildBVH(all_obj, nb);

    // OBJET* all_obj2 = malloc(nb*sizeof(OBJET));
    // all_obj2[0] = BuildBox((vector){0,10,-10}, 500, 500, 20, c_blanc);
    // all_obj2[1] = BuildSphere((vector){10, 70, 5}, 20, c_iceberg);
    // all_obj2[2] = BuildRotY(BuildTor((vector){10, 40, 10}, 7, 2, c_iceberg), 2);
    // all_obj2[3] = BuildTriangle((vector){10, 40, 10}, (vector){0,1,2}, (vector){0,0,0}, c_rouge);
    // BVHNode* root2 = buildBVH(all_obj2, nb);

    // BVHNode* roots[2];
    // roots[0] = root1;
    // roots[1] = root2;
    // BVHNode* root = MergeBVH(roots, 2);

    // printf("%d\n", root->obj_count);

    BVHNode* root = BVH_Maison();
    printf("%d\n", root->obj_count);

    freeBVH(root);

    return 0;

}
