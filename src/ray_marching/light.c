#include "light.h"
extern stats_opti STATS;

color c_rouge = {255,0,0,1.0};
color c_bleu = {0,0,255,1.0};
color c_vert = {0,255,0,1.0};
color c_noir = {0,0,0,1.0};
color c_blanc = {255,255,255,1.0};
color c_gris = {63, 63, 63,1.0};
color c_fond = {0,0,255,1.0};
color c_orange = {255,165,0,1.0};
color c_bistre = {61,43,31,1.0};
color c_bleu_berlin = {36,68,92,1.0};
color c_iceberg = {113, 166, 210, 1.0};
color c_jaune = {255,255,0,1.0};

color c_canape = {230,119,75,1.0};
color c_trombone = {202,146,53,1.0};
color c_bouton = {90, 100, 90, 1.0};
color c_sol = {81, 134, 157, 1.0};
color c_mur = {200, 150, 175, 1.0};
color c_commode = {110, 60, 130, 1.0};
color c_tp1 = {200, 150, 110, 1.0};
color c_tp2 = {165, 110, 200, 1.0};
color c_tp3 = {190, 115, 145, 1.0};
color c_tp4 = {210, 128, 144, 1.0};
color c_corbeille = {147, 64, 24, 1.0};
color c_tel = {126, 200, 173, 1.0};
color c_l2 = {165, 68, 119, 1.0};
color c_a2 = {210, 135, 45, 1.0};
color c_tige = {161, 142, 146, 1.0};
color c_l3 = {74, 175, 86, 1.0};
color c_table1 = {60, 70, 90, 1.0};
color c_table2 = {67, 55, 90, 1.0};

color c_feuille = {151,203,76,1.0};
color c_sable = {231,193,120,1.0};
color c_eau = {2,149,203,1.0};
color c_bois = {164, 69, 63, 1.0};
color c_socle = {129,132,225,1.0};

// --- LUMIERES --- //

// renvoie la lumiere avec le prod vect et la normale
float light_diffuse(vector pts, vector source, BVHNode* scene){
    vector v_n = normalise_vecteur(vect_normal(pts, scene));

    float res = fmax(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
    return res;
}


float all_light(vector pts, vector source, BVHNode* scene){
    float res = 0;
    res += light_diffuse(pts, source, scene);
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
float shadow_1(vector pts, vector source, BVHNode* scene){
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
        
        float dist = traverseBVH(scene, position_actuelle, maxsdf).dist;
        
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

float shadow_2(vector pts, vector source, int k, BVHNode* scene){
    float res = 1.0;
    float t = DIST_MIN*100;


    vector rd = normalise_vecteur(get_vec_2_pts(pts, source));

    for (int i = 0; i < MAX_RAY_STEPS && t < MAX_TOTAL_LENGHT; i++){
        float h = traverseBVH(scene, (v_add(pts, v_mult_scal(rd,t))), maxsdf).dist;

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
