#include "ray_marching.h"

extern stats_opti STATS;

// renvoie la couleur d'un rayon avec le ray marching
color ray_marching(ray r, res_SDF (*scene_actuelle)(vector)){
    clock_t begin_r = clock();
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {-10, -20, 50}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){

        res_SDF result_scene = scene_actuelle(position_actuelle);

        float dist = result_scene.dist;

        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            clock_t begin_l = clock();
            float val_light = all_light(position_actuelle, Lumiere, scene_actuelle);       
            clock_t end_l = clock();
            STATS.temps_light += (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            // float val_shadow = shadow_1(position_actuelle, Lumiere, scene_actuelle);
            clock_t begin_s = clock();
            float val_shadow = shadow_2(position_actuelle, Lumiere, 32, scene_actuelle);
            clock_t end_s = clock();
            STATS.temps_shadow += (double)(end_s - begin_s)/CLOCKS_PER_SEC;
            // color res = {150.0, 150.0, 15.0, val_light*val_shadow};
            color res = result_scene.c;
            res.r = brouillard(dist_tot)*res.r + (1-brouillard(dist_tot))*127;
            res.g = brouillard(dist_tot)*res.g + (1-brouillard(dist_tot))*127;
            res.b = brouillard(dist_tot)*res.b + (1-brouillard(dist_tot))*127;


            res.opp = val_light*val_shadow*0.8 + 0.2;
            // res.opp = fmin(val_light, val_shadow)*0.8 + 0.2;
            clock_t end_r = clock();
            STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC - (double)(end_s - begin_s)/CLOCKS_PER_SEC - (double)(end_l - begin_l)/CLOCKS_PER_SEC;
            STATS.nb_rayons_tot += 1;
            STATS.nb_rayons_etapes += i+1;
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            clock_t end_r = clock();
            STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
            STATS.nb_rayons_tot += 1;
            STATS.nb_rayons_etapes += i+1;
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    clock_t end_r = clock();
    STATS.temps_raymarch += (double)(end_r - begin_r)/CLOCKS_PER_SEC;
    STATS.nb_rayons_etapes += MAX_RAY_STEPS;
    STATS.nb_rayons_tot += 1;
    return c_rouge;
}


vector get_normal_paysage(vector pts){
    return normalise_vecteur((vector){nurbs_paysage(pts.x - EPSILON,pts.y) - nurbs_paysage(pts.x + EPSILON, pts.y),2*EPSILON,nurbs_paysage(pts.x, pts.y-EPSILON) - nurbs_paysage(pts.x, pts.y+EPSILON)});
}


color ray_marching_paysage(ray r, res_SDF (*scene_actuelle)(vector)){
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {10, 10, 50}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){

        res_SDF result_scene = scene_actuelle(position_actuelle);

        float dist = result_scene.dist;

        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            // float val_light = all_light(position_actuelle, Lumiere, scene_actuelle);       
            // float val_shadow = shadow_1(position_actuelle, Lumiere, scene_actuelle);
            // float val_shadow = shadow_2((vector){position_actuelle.x,position_actuelle.y, nurbs_paysage(position_actuelle.x, position_actuelle.y) + 2*DIST_MIN}, Lumiere, 32, scene_actuelle);
            float val_shadow = shadow_2(position_actuelle, Lumiere, 32, scene_actuelle);

            color res = result_scene.c;
            res.r = brouillard(dist_tot)*res.r + (1-brouillard(dist_tot))*190;
            res.g = brouillard(dist_tot)*res.g + (1-brouillard(dist_tot))*190;
            res.b = brouillard(dist_tot)*res.b + (1-brouillard(dist_tot))*190;

            float val_light = fmax(0,prod_scal(get_normal_paysage(position_actuelle),
                                normalise_vecteur(get_vec_2_pts((vector){position_actuelle.x, position_actuelle.y, nurbs_paysage(position_actuelle.x, position_actuelle.y)},Lumiere))));

            // res.opp = 1.0;
            // res.opp = fmin(val_light, val_shadow)*0.8 + 0.2;
            res.opp = val_light * val_shadow * 0.7 + 0.3;
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    return c_rouge;
}