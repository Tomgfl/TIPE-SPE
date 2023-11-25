#include "light.h"
#include "options.h"
#include "utiles.h"
#include "signed_distance_function.h"



// --- LUMIERES --- //

// renvoie la lumiere avec le prod vect et la normale
float light_diffuse(coord pts, coord source){
    vector v_n = normalise_vecteur(vect_normal(pts));
    float res = max(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
    return res;
}


float all_light(coord pts, coord source){
    float res = 0;
    res += light_diffuse(pts, source);
    res += 0.3; // lumiere ambiante

    return res;
}




// --- OMBRES --- //

// fait un ray marching entre le point et la source de lumiere (pas le plus opti je pense)
float shadow_1(coord pts, coord source){
    vector direction = normalise_vecteur(get_vec_2_pts(pts, source));
    coord position_actuelle = pts;

    float dist_tot = 0.0;
    position_actuelle.x = pts.x + direction.x * dist_tot;
    position_actuelle.y = pts.y + direction.y * dist_tot;
    position_actuelle.z = pts.z + direction.z * dist_tot;

    for (int i = 0; i < MAX_RAY_STEPS/10; i++){ // on s'éloigne de la surface atteinte
        dist_tot += MIN_ALL_SDF(position_actuelle);
        position_actuelle.x = pts.x + direction.x * dist_tot;
        position_actuelle.y = pts.y + direction.y * dist_tot;
        position_actuelle.z = pts.z + direction.z * dist_tot;
    }
    

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = MIN_ALL_SDF(position_actuelle);
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