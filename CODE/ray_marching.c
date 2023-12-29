#include "ray_marching.h"


// renvoie la couleur d'un rayon avec le ray marching
color ray_marching(ray r){
    float dist_tot = 0.0;
    vector position_actuelle = r.origine;

    vector Lumiere = {-10, -10, 100}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = SCENE_PRINCIPAL(position_actuelle);
        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet

            float val_light = all_light(position_actuelle, Lumiere);

            float val_shadow = shadow_1(position_actuelle, Lumiere);

            color res = {150.0, 150.0, 15.0, val_light*val_shadow};
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