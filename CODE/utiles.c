#include "utiles.h"

// Renvoie le min d'une liste (pour les SDF) (ps : a mettre dans un autre fichier plus tard)
float min_lst (float* lst, int n){
    float fmin = lst[0];
    for (int i = 1; i < n; i++){
        if (lst[i] < fmin){
            fmin = lst[i];
        }
    }
    return fmin;
}



float min(float x, float y){
    if (x < y){
        return x; 
    }
    return y;
}


float max(float x, float y){
    if (x > y){
        return x;
    }
    return y;
}