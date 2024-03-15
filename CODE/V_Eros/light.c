#include "light.h"
extern stats_opti STATS;

color c_rouge = {255,0,0,1.0};
color c_bleu = {0,0,255,1.0};
color c_vert = {0,255,0,1.0};
color c_noir = {0,0,0,1.0};
color c_blanc = {255,255,255,1.0};
color c_gris = {63, 63, 63,1.0};
color c_fond = {135,206,250, 1.0};
color c_orange = {255,165,0,1.0};
color c_bistre = {61,43,31,1.0};
color c_bleu_berlin = {36,68,92,1.0};
color c_iceberg = {113, 166, 210, 1.0};
color c_jaune = {255,255,0,1.0};

// --- LUMIERES --- //

// renvoie la lumiere avec le prod vect et la normale
float light_diffuse(vector pts, vector source, res_SDF(*scene_actuelle)(vector)){
    vector v_n = normalise_vecteur(vect_normal(pts, scene_actuelle));

    float res = fmax(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
    return res;
}


float all_light(vector pts, vector source, res_SDF(*scene_actuelle)(vector)){
    float res = 0;
    res += light_diffuse(pts, source, scene_actuelle);
    // res += 0.4; // lumiere ambiante

    return res;
}




// float light_diffuse_bvh(vector pts, BVHNode* scene, vector source, res_SDF(*scene_actuelle)(BVHNode*, vector, res_SDF)){
//     vector v_n = normalise_vecteur(vect_normal(pts, scene_actuelle));

//     float res = fmax(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
//     return res;
// }
// float all_light_bvh(vector pts, BVHNode* scene, vector source, res_SDF(*scene_actuelle)(BVHNode*, vector, res_SDF)){
//     float res = 0;
//     res += light_diffuse_bvh(pts, scene, source, scene_actuelle);
//     // res += 0.4; // lumiere ambiante

//     return res;
// }





//notion de distance
float brouillard(float t){
    return exp(-0.0005*t);
}




// --- OMBRES --- //

// fait un ray marching entre le point et la source de lumiere (pas le plus opti je pense)
float shadow_1(vector pts, vector source, res_SDF(*scene_actuelle)(vector)){
    vector direction = normalise_vecteur(get_vec_2_pts(pts, source));
    vector position_actuelle = pts;

    float dist_tot = DIST_MIN;
    position_actuelle.x = pts.x ;
    position_actuelle.y = pts.y ;
    position_actuelle.z = pts.z ;

    // for (int i = 0; i < MAX_RAY_STEPS/10; i++){ // on s'éloigne de la surface atteinte
    //     dist_tot += SCENE_PRINCIPAL(position_actuelle).dist;
    //     position_actuelle.x = pts.x + direction.x * dist_tot;
    //     position_actuelle.y = pts.y + direction.y * dist_tot;
    //     position_actuelle.z = pts.z + direction.z * dist_tot;
    // }
    // for (int i = 0; i < MAX_RAY_STEPS/20; i++){
        
    //     float dist = scene_actuelle(position_actuelle).dist;
    //     dist_tot += dist;

    //     if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
    //         return 1.0;
    //     }

    //     position_actuelle.x = pts.x + direction.x * dist_tot;
    //     position_actuelle.y = pts.y + direction.y * dist_tot;
    //     position_actuelle.z = pts.z + direction.z * dist_tot;
        
    // }
    

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = scene_actuelle(position_actuelle).dist;
        
        dist_tot += dist;

        if (dist < DIST_MIN*0.01){
            // STATS.nb_shadow_rayons_tot += 1;
            // STATS.nb_shadow_rayons_etapes += i+1;
            return 0.1;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            // STATS.nb_shadow_rayons_tot += 1;
            // STATS.nb_shadow_rayons_etapes += i+1;
            return 1.0;
        }

        position_actuelle.x = pts.x + direction.x * dist_tot;
        position_actuelle.y = pts.y + direction.y * dist_tot;
        position_actuelle.z = pts.z + direction.z * dist_tot;
        
    }
    // STATS.nb_shadow_rayons_tot += 1;
    // STATS.nb_shadow_rayons_etapes += MAX_RAY_STEPS;

    return 1.0;
}

float shadow_2(vector pts, vector source, int k, res_SDF(*scene_act)(vector)){
    float res = 1.0;
    float t = DIST_MIN*100;


    vector rd = normalise_vecteur(get_vec_2_pts(pts, source));

    for (int i = 0; i < MAX_RAY_STEPS && t < MAX_TOTAL_LENGHT; i++){
        float h = scene_act(v_add(pts, v_mult_scal(rd,t))).dist;

        if (h < DIST_MIN){
            // STATS.nb_shadow_rayons_tot += 1;
            // STATS.nb_shadow_rayons_etapes += i+1;
            return 0.0;
        }
        res = fmin(res, k*h/t);
        t += h;
    }
    // STATS.nb_shadow_rayons_tot += 1;
    // STATS.nb_shadow_rayons_etapes += MAX_RAY_STEPS;
    return res;
}
