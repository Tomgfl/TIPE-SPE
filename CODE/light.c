#include "light.h"


color c_rouge = {255,0,0,1.0};
color c_bleu = {0,0,255,1.0};
color c_vert = {0,255,0,1.0};
color c_noir = {0,0,0,1.0};
color c_blanc = {255,255,255,1.0};
color c_gris = {63, 63, 63,1.0};
color c_fond = {3,27,73,1.0};
color c_orange = {255,165,0,1.0};
color c_bistre = {61,43,31,1.0};
color c_bleu_berlin = {36,68,92,1.0};

// --- LUMIERES --- //

// renvoie la lumiere avec le prod vect et la normale
float light_diffuse(vector pts, vector source){
    vector v_n = normalise_vecteur(vect_normal(pts));
    float res = fmax(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
    return res;
}


float all_light(vector pts, vector source){
    float res = 0;
    res += light_diffuse(pts, source);
    res += 0.3; // lumiere ambiante

    return res;
}




// --- OMBRES --- //

// fait un ray marching entre le point et la source de lumiere (pas le plus opti je pense)
float shadow_1(vector pts, vector source){
    vector direction = normalise_vecteur(get_vec_2_pts(pts, source));
    vector position_actuelle = pts;

    float dist_tot = 0.0;
    position_actuelle.x = pts.x + direction.x * dist_tot;
    position_actuelle.y = pts.y + direction.y * dist_tot;
    position_actuelle.z = pts.z + direction.z * dist_tot;

    for (int i = 0; i < MAX_RAY_STEPS/10; i++){ // on s'éloigne de la surface atteinte
        dist_tot += SCENE_PRINCIPAL(position_actuelle).dist;
        position_actuelle.x = pts.x + direction.x * dist_tot;
        position_actuelle.y = pts.y + direction.y * dist_tot;
        position_actuelle.z = pts.z + direction.z * dist_tot;
    }
    

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = SCENE_PRINCIPAL(position_actuelle).dist;
        dist_tot += dist;

        if (dist < DIST_MIN*0.01){
            return 0.0;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            return 1.0;
        }

        position_actuelle.x = pts.x + direction.x * dist_tot;
        position_actuelle.y = pts.y + direction.y * dist_tot;
        position_actuelle.z = pts.z + direction.z * dist_tot;
        
    }

    return 1.0;
}


