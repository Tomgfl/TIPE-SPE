#ifndef UTILES_H 
#define UTILES_H

float min_lst (float* lst, int n);
// float MIN(float x, float y);
// float MAX(float x, float y);

// structure pour le resultat d'un systeme 2 2 
struct res_systeme_2_s{
    float det;
    float x;
    float y; 
};
typedef struct res_systeme_2_s res_systeme_2;


res_systeme_2 solve_systeme_2(float a, float b, float c, float d, float alpha, float beta);

#endif 