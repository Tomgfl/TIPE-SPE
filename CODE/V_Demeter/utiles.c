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

RES_SDF min_lst_sdf(RES_SDF* lst, int n){
    RES_SDF res = lst[0];

    for (int i = 1; i < n; i++){
        res = min_sdf(res, lst[i]);
    }
    return res;
}

// ax + by = alpha
// cx + dy = beta
// Renvoie une solution seulement si le determinant est non nul
RES_SYS_2 solve_systeme_2(float a, float b, float c, float d, float alpha, float beta){
    RES_SYS_2 res;

    res.det = a*d - b*c;

    if (res.det != 0.0 || res.det != -0.0){
        res.x = (d * alpha - b * beta)/res.det;
        res.y = (a * beta - c * alpha)/res.det;
        return res;
    }
    res.x = 1.0;
    res.y = 1.0;
    return res;
}

RES_SDF min_sdf(RES_SDF d1, RES_SDF d2){
    if (d1.dist < d2.dist){
        return d1;
    }
    return d2;
}

RES_SDF max_sdf(RES_SDF d1, RES_SDF d2){
    if (d1.dist > d2.dist){
        return d1;
    }
    return d2;
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


float** create_2d_tab(int n, int m, float val){
    float** res = malloc(n*sizeof(float*));
    for (int i = 0; i < n; i++){
        res[i] = malloc(m*sizeof(float));
        for (int j = 0; j < m; j++){
            res[i][j] = val;
        }
    }    
    return res;
}


void free_tab_2d(float** tab, int n){
    for (int i = 0; i < n; i++){
        free(tab[i]);
    }
    free(tab);
    return;
}
