#include "utiles.h"

// Renvoie le min d'une liste (pour les SDF) (ps : a mettre dans un autre fichier plus tard)
float min_lst (float* lst, int n){
    float val_min = lst[0];
    for (int i = 1; i < n; i++){
        if (lst[i] < val_min){
            val_min = lst[i];
        }
    }
    return val_min;
}

// #define MIN(i, j) (((i) < (j)) ? (i) : (j))
// #define MAX(i, j) (((i) > (j)) ? (i) : (j))
// #define SIGN(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)
// #define CLAMP(d, min, max) (((d) < (min)) ? (min) : (((d) > (max)) ? (max) : (d)))


// float MIN(float x, float y){
//     if (x < y){
//         return x; 
//     }
//     return y;
// }


// float MAX(float x, float y){
//     if (x > y){
//         return x;
//     }
//     return y;
// }