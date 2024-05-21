#include "ray_marching.h"

// extern stats_opti STATS;

// renvoie la couleur d'un rayon avec le ray marching
color ray_marching(ray r, res_SDF (*scene_actuelle)(vector)){
    // clock_t begin_r = clock();
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {0, 30, 50}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){

        res_SDF result_scene = scene_actuelle(position_actuelle);

        float dist = result_scene.dist;

        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            // clock_t begin_l = clock();
            float val_light = all_light(position_actuelle, Lumiere, scene_actuelle);
            // clock_t end_l = clock();
            // STATS.temps_light += (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            // float val_light = 1;
            // float val_shadow = 1;
            // float val_shadow = shadow_1(position_actuelle, Lumiere, scene_actuelle);
            // clock_t begin_s = clock();
            float val_shadow = shadow_2(position_actuelle, Lumiere, 32, scene_actuelle);
            // float val_shadow = 1.0;
            // clock_t end_s = clock();
            // STATS.temps_shadow += (double)(end_s - begin_s)/CLOCKS_PER_SEC;
            // color res = {150.0, 150.0, 15.0, val_light*val_shadow};
            color res = result_scene.c;
            res.r = brouillard(dist_tot)*res.r + (1-brouillard(dist_tot))*127;
            res.g = brouillard(dist_tot)*res.g + (1-brouillard(dist_tot))*127;
            res.b = brouillard(dist_tot)*res.b + (1-brouillard(dist_tot))*127;


            res.opp = val_light*val_shadow*0.8 + 0.2;
            // res.opp = fmin(val_light, val_shadow)*0.8 + 0.2;
            // clock_t end_r = clock();
            // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC - (double)(end_s - begin_s)/CLOCKS_PER_SEC - (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            // STATS.nb_rayons_tot += 1;
            // STATS.nb_rayons_etapes += i+1;
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            // clock_t end_r = clock();
            // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
            // STATS.nb_rayons_tot += 1;
            // STATS.nb_rayons_etapes += i+1;
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    // clock_t end_r = clock();
    // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
    // STATS.nb_rayons_etapes += MAX_RAY_STEPS;
    // STATS.nb_rayons_tot += 1;
    return c_rouge;
}


// void* ray_marching_thread(void* ptr_args){
//     arg* a = (arg*) ptr_args;
//     for (int i = a->id*WIDTH/NB_THREADS; i < (a->id+1)*WIDTH/NB_THREADS; i++){
//         for (int j = 0; j < HEIGHT; j++){
//             a->t_out[i][j] = ray_marching(a->t_in[i][j], a->fct_scene);
//         }
//     }
//     return NULL;
// }


void* ray_marching_bvh_thread(void* ptr_args){
    arg* a = (arg*) ptr_args;
    for (int i = a->id*WIDTH/NB_THREADS; i < (a->id+1)*WIDTH/NB_THREADS; i++){
        for (int j = 0; j < HEIGHT; j++){
            a->t_out[i][j] = ray_marching_bvh(a->t_in[i][j], a->bvh, a->fct_scene, a->fct_scene_bvh, a->n, a->m, a->c);
        }
    }
    return NULL;
}


color ray_marching_bvh(ray r, BVHNode* scene, res_SDF (*scene_actuelle)(vector), res_SDF (*scene_bvh)(BVHNode*, vector, res_SDF), vector n, vector m, color c){
    // clock_t begin_r = clock();
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {0,0,20}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){

        res_SDF sdf_plan = SDF_plan(position_actuelle, n, m, c);

        res_SDF result_scene = scene_bvh(scene, position_actuelle, sdf_plan);

        float dist = result_scene.dist;

        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            // clock_t begin_l = clock();
            float val_light = all_light(position_actuelle, Lumiere, scene_actuelle);
            // clock_t end_l = clock();
            // STATS.temps_light += (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            // float val_light = 1;
            // clock_t begin_s = clock();
            float val_shadow = shadow_2(position_actuelle, Lumiere, 32, scene_actuelle);
            // float val_shadow = 1.0;
            // clock_t end_s = clock();
            // STATS.temps_shadow += (double)(end_s - begin_s)/CLOCKS_PER_SEC;
            // color res = {150.0, 150.0, 15.0, val_light*val_shadow};
            color res = result_scene.c;
            res.r = brouillard(dist_tot)*res.r + (1-brouillard(dist_tot))*127;
            res.g = brouillard(dist_tot)*res.g + (1-brouillard(dist_tot))*127;
            res.b = brouillard(dist_tot)*res.b + (1-brouillard(dist_tot))*127;


            res.opp = val_light*val_shadow*0.8 + 0.2;
            // res.opp = fmin(val_light, val_shadow)*0.8 + 0.2;
            // clock_t end_r = clock();
            // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC - (double)(end_s - begin_s)/CLOCKS_PER_SEC - (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            // STATS.nb_rayons_tot += 1;
            // STATS.nb_rayons_etapes += i+1;
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            // clock_t end_r = clock();
            // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
            // STATS.nb_rayons_tot += 1;
            // STATS.nb_rayons_etapes += i+1;
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    // clock_t end_r = clock();
    // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
    // STATS.nb_rayons_etapes += MAX_RAY_STEPS;
    // STATS.nb_rayons_tot += 1;
    return c_rouge;
}


color ray_marching_bvhNoPlan(ray r, BVHNode* scene, res_SDF (*scene_actuelle)(vector), res_SDF (*scene_bvh)(BVHNode*, vector)){
    // clock_t begin_r = clock();
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {0, 30, 50}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){

        res_SDF result_scene = scene_bvh(scene, position_actuelle);

        float dist = result_scene.dist;

        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            float val_light = all_light(position_actuelle, Lumiere, scene_actuelle);
            float val_shadow = shadow_2(position_actuelle, Lumiere, 32, scene_actuelle);
            // float val_shadow = 1.0;
            color res = result_scene.c;
            res.r = brouillard(dist_tot)*res.r + (1-brouillard(dist_tot))*127;
            res.g = brouillard(dist_tot)*res.g + (1-brouillard(dist_tot))*127;
            res.b = brouillard(dist_tot)*res.b + (1-brouillard(dist_tot))*127;


            res.opp = val_light*val_shadow*0.8 + 0.2;
        
            // res.opp = fmin(val_light, val_shadow)*0.8 + 0.2;
            // clock_t end_r = clock();
            // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC - (double)(end_s - begin_s)/CLOCKS_PER_SEC - (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            // STATS.nb_rayons_tot += 1;
            // STATS.nb_rayons_etapes += i+1;
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            // clock_t end_r = clock();
            // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
            // STATS.nb_rayons_tot += 1;
            // STATS.nb_rayons_etapes += i+1;
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    // clock_t end_r = clock();
    // STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
    // STATS.nb_rayons_etapes += MAX_RAY_STEPS;
    // STATS.nb_rayons_tot += 1;
    return c_rouge;
}





color ray_marching_bvh_moving(ray r, BVHNode* scene, res_SDF (*scene_actuelle)(vector), res_SDF (*scene_bvh)(BVHNode*, vector)){
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {0, 30, 50}; // lumiere mis a la mano
    BVHNode* Scene2 = SCENE_MOUVANTE();   // Arbre contenant les objets mouvants

    for (int i = 0; i < MAX_RAY_STEPS; i++){

        res_SDF result_fix = scene_bvh(scene, position_actuelle);
        res_SDF result_move = scene_bvh(Scene2, position_actuelle);
        res_SDF result_scene = min_sdf(result_fix, result_move);

        float dist = result_scene.dist;

        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            float val_light = all_light(position_actuelle, Lumiere, scene_actuelle);
            float val_shadow = shadow_2(position_actuelle, Lumiere, 32, scene_actuelle);
            // float val_shadow = 1.0;
            color res = result_scene.c;
            res.r = brouillard(dist_tot)*res.r + (1-brouillard(dist_tot))*127;
            res.g = brouillard(dist_tot)*res.g + (1-brouillard(dist_tot))*127;
            res.b = brouillard(dist_tot)*res.b + (1-brouillard(dist_tot))*127;


            res.opp = val_light*val_shadow*0.8 + 0.2;
            freeBVH(Scene2);
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            freeBVH(Scene2);
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }
    freeBVH(Scene2);
    return c_rouge;
}