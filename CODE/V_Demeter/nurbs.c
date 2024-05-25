#include "nurbs.h"

extern STATS_NURBS Stats_nurbs;
pthread_mutex_t verrou;
extern float time_scene;

// aloue la memoire pour un cnet
CNET create_cnet(int n, int m){
    CNET res = malloc(sizeof(struct cnet_s));
    res->n = n;
    res->m = m;
    res->Pw = malloc(n*sizeof(CPOINT*));
    for (int i = 0; i < n; i++){
        res->Pw[i] = malloc(m*sizeof(CPOINT));
    }
    return res;
}

void free_cnet(CNET net){
    for (int i = 0; i < net->n; i++){
        free(net->Pw[i]);
    }
    free(net->Pw);
    free(net);
    return;
}

KNOTVECTOR create_knotvector(int m){
    KNOTVECTOR res = malloc(sizeof(struct knotvector_s));
    res->m = m;
    res->U = malloc(m*sizeof(float));
    return res;
}

void free_knotvector(KNOTVECTOR knot){
    free(knot->U);
    free(knot);
    return;
}

SURFACE create_surface(int p, int q){
    SURFACE res = malloc(sizeof(struct surface_s));
    res->p = p; res->q = q;
    return res;
}

void free_surface(SURFACE surf){
    free_cnet(surf->net);
    free_knotvector(surf->knu);
    free_knotvector(surf->knv);
    free(surf);
    return;
}


SURFACE nurbs_1(){
    SURFACE res = create_surface(2,2);

    CNET net = create_cnet(4,3);
    net->Pw[0][0] = (CPOINT){-3,4,0,1};
    net->Pw[1][0] = (CPOINT){1,4,0,1};
    net->Pw[2][0] = (CPOINT){4,4,2,1};
    net->Pw[3][0] = (CPOINT){6,5,2,1}; 
    net->Pw[0][1] = (CPOINT){-4,2,0,1};
    net->Pw[1][1] = (CPOINT){-2,2,1,1};
    net->Pw[2][1] = (CPOINT){2,2,2,1};
    net->Pw[3][1] = (CPOINT){6,2,1,1}; 
    net->Pw[0][2] = (CPOINT){-6,-2,-1,1};
    net->Pw[1][2] = (CPOINT){-2,-2,0,1};
    net->Pw[2][2] = (CPOINT){2,-2,1,1};
    net->Pw[3][2] = (CPOINT){4,-2,2,1};
    res->net = net;

    KNOTVECTOR knu = create_knotvector(7);
    knu->U[0] = 0;
    knu->U[1] = 0;
    knu->U[2] = 0;
    knu->U[3] = 1.0/2.0;
    knu->U[4] = 1;
    knu->U[5] = 1;
    knu->U[6] = 1;
    res->knu = knu;

    KNOTVECTOR knv = create_knotvector(6);
    knv->U[0] = 0;
    knv->U[1] = 0;
    knv->U[2] = 0;
    knv->U[3] = 1;
    knv->U[4] = 1;
    knv->U[5] = 1;
    res->knv = knv;
    return res;
}


SURFACE nurbs_2(){
    SURFACE res = create_surface(3,3);

    CNET net = create_cnet(5,5);
    net->Pw[0][0] = (CPOINT){-6,-3.8,1,1};
    net->Pw[1][0] = (CPOINT){-5,-2.3,0.7,1};
    net->Pw[2][0] = (CPOINT){-6,1,1,1};
    net->Pw[3][0] = (CPOINT){-5.8,3.4,1.1,1}; 
    net->Pw[4][0] = (CPOINT){-5.4,5.2,1.5,1};

    net->Pw[0][1] = (CPOINT){-3.14,-4.5,0.6,1};
    net->Pw[1][1] = (CPOINT){-3.5,-2.9,1.3,1};
    net->Pw[2][1] = (CPOINT){-3.8,-0.9,1.9,1};
    net->Pw[3][1] = (CPOINT){-4.24,0.8,0.8,1}; 
    net->Pw[4][1] = (CPOINT){-4,3.2,2,1};

    net->Pw[0][2] = (CPOINT){-1.46,-5.4,1,1};
    net->Pw[1][2] = (CPOINT){-1.7,-3.9,1.21,1};
    net->Pw[2][2] = (CPOINT){-1.72,-2.9,1.3,1};
    net->Pw[3][2] = (CPOINT){-2.3,1.54,0.42,1};
    net->Pw[4][2] = (CPOINT){-2.4,3.2,1.5,1};

    net->Pw[0][3] = (CPOINT){1.5,-6.8,0,1};
    net->Pw[1][3] = (CPOINT){1.3,-4,0.85,1};
    net->Pw[2][3] = (CPOINT){1.8,-2.5,1.01,1};
    net->Pw[3][3] = (CPOINT){1.6,0.97,0.6,1};
    net->Pw[4][3] = (CPOINT){1.68,2.08,0.2,1};

    net->Pw[0][4] = (CPOINT){3.73,-7.47,-1.15,1};
    net->Pw[1][4] = (CPOINT){3.72,-5.5,-0.81,1};
    net->Pw[2][4] = (CPOINT){3.52,-4.14,-0.96,1};
    net->Pw[3][4] = (CPOINT){3.73,-3.15,-0.7,1};
    net->Pw[4][4] = (CPOINT){3.44,1.41,-0.7,1};
    res->net = net;

    KNOTVECTOR knu = create_knotvector(9);
    knu->U[0] = 0;
    knu->U[1] = 0;
    knu->U[2] = 0;
    knu->U[3] = 0;
    knu->U[4] = 1.0/2.0;
    knu->U[5] = 1;
    knu->U[6] = 1;
    knu->U[7] = 1;
    knu->U[8] = 1;
    res->knu = knu;

    KNOTVECTOR knv = create_knotvector(9);
    knv->U[0] = 0;
    knv->U[1] = 0;
    knv->U[2] = 0;
    knv->U[3] = 0;
    knv->U[4] = 1.0/2.0;
    knv->U[5] = 1;
    knv->U[6] = 1;
    knv->U[7] = 1;
    knv->U[8] = 1;
    res->knv = knv;
    return res;
}



SURFACE nurbs_rd(){
    SURFACE res = create_surface(3,3);

    CNET net = create_cnet(5,5);
    net->Pw[0][0] = (CPOINT){-6,-4,3 + sin(1.0*time_scene),1};
    net->Pw[1][0] = (CPOINT){-6,-2,3 + cos(2.0*time_scene),1};
    net->Pw[2][0] = (CPOINT){-6,0,3 + tan(3.0*time_scene),1};
    net->Pw[3][0] = (CPOINT){-6,2,3 + sin(4.0*time_scene),1}; 
    net->Pw[4][0] = (CPOINT){-6,4,3 + cos(5.0*time_scene),1};

    net->Pw[0][1] = (CPOINT){-4,-4,3 + tan(2.0*time_scene),1};
    net->Pw[1][1] = (CPOINT){-4,-2,3 + cos(3.0*time_scene),1};
    net->Pw[2][1] = (CPOINT){-4,0,3 + tan(4.0*time_scene),1};
    net->Pw[3][1] = (CPOINT){-4,2,3 + sin(5.0*time_scene),1}; 
    net->Pw[4][1] = (CPOINT){-4,4,3 + cos(1.0*time_scene),1};

    net->Pw[0][2] = (CPOINT){-2,-4,3 + tan(3.0*time_scene),1};
    net->Pw[1][2] = (CPOINT){-2,-2,3 + cos(4.0*time_scene),1};
    net->Pw[2][2] = (CPOINT){-2,0,3 + sin(5.0*time_scene),1};
    net->Pw[3][2] = (CPOINT){-2,2,3 + cos(1.0*time_scene),1};
    net->Pw[4][2] = (CPOINT){-2,4,3 + tan(2.0*time_scene),1};

    net->Pw[0][3] = (CPOINT){0,-4,3 + sin(4.0*time_scene),1};
    net->Pw[1][3] = (CPOINT){0,-2,3 + cos(5.0*time_scene),1};
    net->Pw[2][3] = (CPOINT){0,0,3 + tan(1.0*time_scene),1};
    net->Pw[3][3] = (CPOINT){0,2,3 + sin(2.0*time_scene),1};
    net->Pw[4][3] = (CPOINT){0,4,3 + cos(3.0*time_scene),1};

    net->Pw[0][4] = (CPOINT){2,-4,3 + tan(5.0*time_scene),1};
    net->Pw[1][4] = (CPOINT){2,-2,3 + sin(1.0*time_scene),1};
    net->Pw[2][4] = (CPOINT){2,0,3 + cos(2.0*time_scene),1};
    net->Pw[3][4] = (CPOINT){2,2,3 + tan(3.0*time_scene),1};
    net->Pw[4][4] = (CPOINT){2,4,3 + sin(4.0*time_scene),1};
    res->net = net;

    KNOTVECTOR knu = create_knotvector(9);
    knu->U[0] = 0;
    knu->U[1] = 0;
    knu->U[2] = 0;
    knu->U[3] = 0;
    knu->U[4] = 1.0/2.0;
    knu->U[5] = 1;
    knu->U[6] = 1;
    knu->U[7] = 1;
    knu->U[8] = 1;
    res->knu = knu;

    KNOTVECTOR knv = create_knotvector(9);
    knv->U[0] = 0;
    knv->U[1] = 0;
    knv->U[2] = 0;
    knv->U[3] = 0;
    knv->U[4] = 1.0/2.0;
    knv->U[5] = 1;
    knv->U[6] = 1;
    knv->U[7] = 1;
    knv->U[8] = 1;
    res->knv = knv;
    return res;
}




// Fonction de base Nij associer a U
float N_nurbs(int i, int p, float u, KNOTVECTOR U){
    // printf("N : %d | %d \n", i, p);
    // printf("-- %f --\n", u);
    if (p == 0){
        if ((U->U[i] <= u) && (u < U->U[i+1])){
            return 1.0;
        } else {
            return 0.0;
        }
    } else {       
        float t1, t2;
        if (U->U[i+p] - U->U[i] == 0){
            t1 = 0.0;
        } else {
            t1 = (u - U->U[i])/(U->U[i+p] - U->U[i]);
        }

        if (U->U[i+p+1] - U->U[i+1] == 0){
            t2 = 0.0;
        } else {
            t2 = (U->U[i+p+1] - u)/(U->U[i+p+1] - U->U[i+1]);
        }

        return t1*N_nurbs(i, p-1, u, U) + t2*N_nurbs(i+1, p-1, u, U);
    }
}


float dN_nurbs(int i, int p, float u, KNOTVECTOR U){
    float t1, t2;
    if (U->U[i+p] - U->U[i] == 0.0){
        t1 = 0.0;
    } else {
        t1 = p/(U->U[i+p] - U->U[i]);
    }

    if (U->U[i+p+1] - U->U[i+1] == 0.0){
        t2 = 0.0;
    } else {
        t2 = p/(U->U[i+p+1] - U->U[i+1]);
    }

    return t1*N_nurbs(i, p-1, u, U) - t2*N_nurbs(i+1, p-1, u, U);
}


float dkN_nurbs(int k, int i, int p, float u, KNOTVECTOR U){
    if (k == 0){
        return N_nurbs(i, p, u, U);
    }

    float t1, t2;
    if (U->U[i+p] - U->U[i] == 0.0){
        t1 = 0.0;
    } else {
        t1 = p/(U->U[i+p] - U->U[i]);
    }

    if (U->U[i+p+1] - U->U[i+1] == 0.0){
        t2 = 0.0;
    } else {
        t2 = p/(U->U[i+p+1] - U->U[i+1]);
    }
    
    return t1*dkN_nurbs(k-1, i, p-1, u, U) - t2*dkN_nurbs(k-1, i+1, p-1, u, U);
}





void affiche_surface(SURFACE s){
    printf("p : %d\n",s->p);
    printf("q : %d\n",s->q);

    printf("U : ");
    for (int i = 0; i < s->knu->m; i++){
        printf("%.2f|",s->knu->U[i]);
    }
    printf("\n");

    printf("V : ");
    for (int i = 0; i < s->knv->m; i++){
        printf("%.2f|",s->knv->U[i]);
    }
    printf("\n");

    printf("NET (%d)(%d) : \n",s->net->n, s->net->m);
    for (int i = 0; i < s->net->n; i++){
        for (int j = 0; j < s->net->m; j++){
            printf("{%.2f, %.2f, %.2f : %.2f}",s->net->Pw[i][j].x, s->net->Pw[i][j].y, s->net->Pw[i][j].z, s->net->Pw[i][j].w);
        }
        printf("\n");
    }
    printf("\n");
    return;
}



// --- V1 - (pas opti) --- //
VECTOR R_nurbs(float u, float v, SURFACE s){
    VECTOR res = {0.0 ,0.0 ,0.0};
    for (int i = 0; i < s->net->n; i++){
        for (int j = 0; j < s->net->m; j++){
            float N_w = N_nurbs(i, s->p, u, s->knu)*N_nurbs(j, s->q, v, s->knv)*s->net->Pw[i][j].w;
            res.x += N_w*s->net->Pw[i][j].x;
            res.y += N_w*s->net->Pw[i][j].y;
            res.z += N_w*s->net->Pw[i][j].z;
        }
    }
    return res;
}

float D_nurbs(float u, float v, SURFACE s){
    float res = 0.0;
    for (int i = 0; i < s->net->n; i++){
        for (int j = 0; j < s->net->m; j++){
            res += N_nurbs(i, s->p, u, s->knu)*N_nurbs(j, s->q, v, s->knv)*s->net->Pw[i][j].w;
        }
    }
    return res;
}

VECTOR S_nurbs(float u, float v, SURFACE s){
    float D = D_nurbs(u, v, s);

    if (D != 0){
        VECTOR R = R_nurbs(u, v, s);
        return (VECTOR){R.x/D, R.y/D, R.z/D};
    }
    printf("Erreur : D = 0 (S), %f, %f\n", u, v);
    return (VECTOR){0.0,0.0,0.0}; 
}

VECTOR dR_ku_lv_nurbs(int k, int l, float u, float v, SURFACE s){
    VECTOR res = {0.0 ,0.0 ,0.0};
    for (int i = 0; i < s->net->n; i++){
        for (int j = 0; j < s->net->m; j++){
            float N_w = dkN_nurbs(k, i, s->p, u, s->knu)*dkN_nurbs(l, j, s->q, v, s->knv)*s->net->Pw[i][j].w;
            res.x += N_w*s->net->Pw[i][j].x;
            res.y += N_w*s->net->Pw[i][j].y;
            res.z += N_w*s->net->Pw[i][j].z;
        }
    }
    return res;
}

float dD_ku_lv_nurbs(int k, int l, float u, float v, SURFACE s){
    float res = 0.0;
    for (int i = 0; i < s->net->n; i++){
        for (int j = 0; j < s->net->m; j++){
            res += dkN_nurbs(k, i, s->p, u, s->knu)*dkN_nurbs(l, j, s->q, v, s->knv)*s->net->Pw[i][j].w;
        }
    }
    return res;
}

VECTOR S_u_nurbs(float u, float v, SURFACE s){
    if (u == 0.0 && v == 0.0){
        if (s->knu->U[s->p+1] == 0){
            return (VECTOR){0.0,0.0,0.0};
        }
        VECTOR res;
        float t = (s->p * s->net->Pw[1][0].w)/(s->knu->U[s->p + 1] * s->net->Pw[0][0].w);
        res.x = t*(s->net->Pw[1][0].x - s->net->Pw[0][0].x);
        res.y = t*(s->net->Pw[1][0].y - s->net->Pw[0][0].y);
        res.z = t*(s->net->Pw[1][0].z - s->net->Pw[0][0].z);
        return res;
    }
    
    float D = D_nurbs(u,v,s);
    if (D == 0.0){
        printf("Erreur : D = 0 (S_u)\n");
        return (VECTOR){0.0,0.0,0.0};
    }
    VECTOR Ru = dR_ku_lv_nurbs(1,0,u,v,s);
    float Du = dD_ku_lv_nurbs(1,0,u,v,s);
    VECTOR S = S_nurbs(u, v, s);

    VECTOR res;
    res.x = (Ru.x - Du*S.x)/D;
    res.y = (Ru.y - Du*S.y)/D;
    res.z = (Ru.z - Du*S.z)/D;
    return res;
}

VECTOR S_v_nurbs(float u, float v, SURFACE s){
    if (u == 0.0 && v == 0.0){
        if (s->knv->U[s->q+1] == 0){
            return (VECTOR){0.0,0.0,0.0};
        }
        VECTOR res;
        float t = (s->q * s->net->Pw[0][1].w)/(s->knv->U[s->q + 1] * s->net->Pw[0][0].w);
        res.x = t*(s->net->Pw[0][1].x - s->net->Pw[0][0].x);
        res.y = t*(s->net->Pw[0][1].y - s->net->Pw[0][0].y);
        res.z = t*(s->net->Pw[0][1].z - s->net->Pw[0][0].z);
        return res;
    }

    float D = D_nurbs(u,v,s);
    if (D == 0.0){
        printf("Erreur : D = 0 (S_v)\n");
        return (VECTOR){0.0,0.0,0.0};
    }
    VECTOR Rv = dR_ku_lv_nurbs(0,1,u,v,s);
    float Dv = dD_ku_lv_nurbs(0,1,u,v,s);
    VECTOR S = S_nurbs(u, v, s);

    VECTOR res;
    res.x = (Rv.x - Dv*S.x)/D;
    res.y = (Rv.y - Dv*S.y)/D;
    res.z = (Rv.z - Dv*S.z)/D;
    return res;
}

VECTOR S_uv_nurbs(float u, float v, SURFACE s){    
    float D = D_nurbs(u, v, s);
    if (D == 0.0){
        printf("Erreur : D = 0 (S_uv)\n");
        return (VECTOR){0.0,0.0,0.0};
    }
    VECTOR Ruv = dR_ku_lv_nurbs(1, 1, u, v, s);
    float Duv = dD_ku_lv_nurbs(1, 1, u, v, s);
    float Du = dD_ku_lv_nurbs(1, 0, u, v, s);
    float Dv = dD_ku_lv_nurbs(0, 1, u, v, s);
    VECTOR S = S_nurbs(u, v, s);
    VECTOR Su = S_u_nurbs(u, v, s);
    VECTOR Sv = S_v_nurbs(u, v, s);

    VECTOR res;
    res.x = (Ruv.x - Duv*S.x - Du*Sv.x - Dv*Su.x)/D;
    res.y = (Ruv.y - Duv*S.y - Du*Sv.y - Dv*Su.y)/D;
    res.z = (Ruv.z - Duv*S.z - Du*Sv.z - Dv*Su.z)/D;
    return res;
}

VECTOR S_uu_nurbs(float u, float v, SURFACE s){
    float D = D_nurbs(u, v, s);
    if (D == 0.0){
        printf("Erreur : D = 0 (S_uu)\n");
        return (VECTOR){0.0,0.0,0.0};
    }
    VECTOR Ruu = dR_ku_lv_nurbs(2, 0, u, v, s);
    float Du = dD_ku_lv_nurbs(1, 0, u, v, s);
    float Duu = dD_ku_lv_nurbs(2, 0, u, v, s);
    VECTOR S = S_nurbs(u, v, s);
    VECTOR Su = S_u_nurbs(u, v, s);

    VECTOR res;
    res.x = (Ruu.x - 2*Du*Su.x - Duu*S.x)/D;
    res.y = (Ruu.y - 2*Du*Su.y - Duu*S.y)/D;
    res.z = (Ruu.z - 2*Du*Su.z - Duu*S.z)/D;
    return res;
}

VECTOR S_vv_nurbs(float u, float v, SURFACE s){
    float D = D_nurbs(u, v, s);
    if (D == 0.0){
        printf("Erreur : D = 0 (S_vv)\n");
        return (VECTOR){0.0,0.0,0.0};
    }
    VECTOR Rvv = dR_ku_lv_nurbs(0, 2, u, v, s);
    float Dv = dD_ku_lv_nurbs(0, 1, u, v, s);
    float Dvv = dD_ku_lv_nurbs(0, 2, u, v, s);
    VECTOR S = S_nurbs(u, v, s);
    VECTOR Sv = S_v_nurbs(u, v, s);

    VECTOR res;
    res.x = (Rvv.x - 2*Dv*Sv.x - Dvv*S.x)/D;
    res.y = (Rvv.y - 2*Dv*Sv.y - Dvv*S.y)/D;
    res.z = (Rvv.z - 2*Dv*Sv.z - Dvv*S.z)/D;
    return res;
}





// ALGO DE PROJECTION
VECTOR r_nurbs(float u, float v, SURFACE s, VECTOR P){
    return v_sub(S_nurbs(u,v,s), P);
}

float f_nurbs(float u, float v, SURFACE s, VECTOR P){
    return prod_scal(r_nurbs(u, v, s, P),S_u_nurbs(u, v, s));
}

float g_nurbs(float u, float v, SURFACE s, VECTOR P){
    return prod_scal(r_nurbs(u, v, s, P),S_v_nurbs(u, v, s));
}

float f_u_nurbs(float u, float v, SURFACE s, VECTOR P){
    return norm_vector(S_u_nurbs(u, v, s))*norm_vector(S_u_nurbs(u, v, s)) + prod_scal(r_nurbs(u, v, s, P), S_uu_nurbs(u, v, s));
}

float f_v_nurbs(float u, float v, SURFACE s, VECTOR P){
    return prod_scal(S_u_nurbs(u, v, s), S_v_nurbs(u, v, s)) + prod_scal(r_nurbs(u, v, s, P), S_uv_nurbs(u, v, s));
}

float g_u_nurbs(float u, float v, SURFACE s, VECTOR P){
    return prod_scal(S_u_nurbs(u, v, s), S_v_nurbs(u, v, s)) + prod_scal(r_nurbs(u, v, s, P), S_uv_nurbs(u, v, s));
}

float g_v_nurbs(float u, float v, SURFACE s, VECTOR P){
    return norm_vector(S_v_nurbs(u, v, s))*norm_vector(S_v_nurbs(u, v, s)) + prod_scal(r_nurbs(u, v, s, P), S_vv_nurbs(u, v, s));
}

float det_sys(float u, float v, SURFACE s, VECTOR P){
    float res = f_u_nurbs(u, v, s, P)*g_v_nurbs(u, v, s, P) - f_v_nurbs(u, v, s, P)*g_u_nurbs(u, v, s, P);
    // printf("det systeme : %f\n", res);
    return res;
}

float next_ui(float u, float v, float det, SURFACE s, VECTOR P){
    if (det == 0.0){
        printf("Erreur : det = 0 (next_ui)\n");
        return 0.0;
    }
    return (g_nurbs(u, v, s, P)*f_v_nurbs(u, v, s, P) - f_nurbs(u, v, s, P)*g_v_nurbs(u, v, s, P))/det;
}

float next_vi(float u, float v, float det, SURFACE s, VECTOR P){
    if (det == 0.0){
        printf("Erreur : det = 0 (next_vi)\n");
        return 0.0;
    }
    return (f_nurbs(u, v, s, P)*g_u_nurbs(u, v, s, P) - g_nurbs(u, v, s, P)*f_u_nurbs(u, v, s, P))/det;
}

// bool crit_1(float u, float v, SURFACE s, VECTOR P){
//     if (norm_vector(r_nurbs(u, v, s, P)) <= EPS_1){
//         return true;
//     }
//     return false;
// }

// bool crit_2(float u, float v, SURFACE s, VECTOR P){
//     if ((fabs(prod_scal(S_u_nurbs(u, v, s),r_nurbs(u, v, s, P))))/(norm_vector(S_u_nurbs(u, v, s))*norm_vector(r_nurbs(u, v, s, P))) <= EPS_2){
//         if ((fabs(prod_scal(S_v_nurbs(u, v, s),r_nurbs(u, v, s, P))))/(norm_vector(S_v_nurbs(u, v, s))*norm_vector(r_nurbs(u, v, s, P))) <= EPS_2){
//             return true;
//         }
//     }
//     return false;
// }


VECTOR projection_nurbs_aux(SURFACE s, VECTOR P, float u_0, float v_0){
    float u = u_0;
    float v = v_0;

    int i = 0;
    VECTOR Q = S_nurbs(u, v, s);
    while (i < 7){ 
        float det = det_sys(u, v, s, P);

        float ui = u;
        float vi = v;

        u = next_ui(ui, vi, det, s, P) + ui;
        v = next_vi(ui, vi, det, s, P) + vi;
        
        if (u < 0){
            u = 0.0;
        }
        if (u >= 1){
            u = 0.999;
        }
        
        if (v < 0){
            v = 0.0;
        }
        if (v >= 1){
            v = 0.999;
        }
        i++;
        VECTOR Q = S_nurbs(u, v, s);       
    }
    return S_nurbs(u, v, s);
}


VECTOR projection_nurbs(SURFACE s, VECTOR P){
    VECTOR Q_1 = projection_nurbs_aux(s, P, 0.0, 0.0);
    VECTOR Q_2 = projection_nurbs_aux(s, P, 0.999, 0.0);
    VECTOR Q_3 = projection_nurbs_aux(s, P, 0.0, 0.999);
    VECTOR Q_4 = projection_nurbs_aux(s, P, 0.999, 0.999);

    float d_1 = dist_2_pts(P, Q_1);
    float d_2 = dist_2_pts(P, Q_2);
    float d_3 = dist_2_pts(P, Q_3);
    float d_4 = dist_2_pts(P, Q_4);

    float d = fmin(fmin(d_1, d_2), fmin(d_3, d_4));

    if (d_1 == d){return Q_1;}
    if (d_2 == d){return Q_2;}
    if (d_3 == d){return Q_3;}
    return Q_4;
}


// Prog dyn
VECTOR projection_nurbs_aux_2(SURFACE s, VECTOR P, float u_0, float v_0){
    int p = s->p; int q = s->q; int n = s->net->n; int m = s->net->m;
    float u = u_0;
    float v = v_0;
    VECTOR S;

        
    for (int iterations = 0; iterations < 40; iterations++){
        float** N_tab_u = N_nurbs_tab(s->knu, u, n, p);
        float** N_tab_v = N_nurbs_tab(s->knv, v, m, q);

        float* dN_tab_u = dN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* dN_tab_v = dN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        float* ddN_tab_u = ddN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* ddN_tab_v = ddN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        // Calcule de R et D
        VECTOR R = {0.0,0.0,0.0};
        VECTOR Ru = {0.0,0.0,0.0};
        VECTOR Rv = {0.0,0.0,0.0};
        VECTOR Ruv = {0.0,0.0,0.0};
        VECTOR Ruu = {0.0,0.0,0.0};
        VECTOR Rvv = {0.0,0.0,0.0};

        float D = 0.0;
        float Du = 0.0;
        float Dv = 0.0;
        float Duv = 0.0;
        float Duu = 0.0;
        float Dvv = 0.0;

        // Calcule des R et D pour les S
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                // R et D
                float temp_1 = N_tab_u[i][p]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                D += temp_1;
                R.x += temp_1*s->net->Pw[i][j].x;
                R.y += temp_1*s->net->Pw[i][j].y;
                R.z += temp_1*s->net->Pw[i][j].z;

                // Ru et Du
                float temp_2 = dN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Du += temp_2;
                Ru.x += temp_2*s->net->Pw[i][j].x;
                Ru.y += temp_2*s->net->Pw[i][j].y;
                Ru.z += temp_2*s->net->Pw[i][j].z;

                // Rv et Dv
                float temp_3 = N_tab_u[i][p]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Dv += temp_3;
                Rv.x += temp_3*s->net->Pw[i][j].x;
                Rv.y += temp_3*s->net->Pw[i][j].y;
                Rv.z += temp_3*s->net->Pw[i][j].z;

                // Ruv et Duv
                float temp_4 = dN_tab_u[i]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Duv += temp_4;
                Ruv.x += temp_4*s->net->Pw[i][j].x;
                Ruv.y += temp_4*s->net->Pw[i][j].y;
                Ruv.z += temp_4*s->net->Pw[i][j].z;

                // Ruu et Duu
                float temp_5 = ddN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Duu += temp_5;
                Ruu.x += temp_5*s->net->Pw[i][j].x;
                Ruu.y += temp_5*s->net->Pw[i][j].y;
                Ruu.z += temp_5*s->net->Pw[i][j].z;

                // Rvv et Dvv
                float temp_6 = N_tab_u[i][p]*ddN_tab_v[j]*s->net->Pw[i][j].w;
                Dvv += temp_6;
                Rvv.x += temp_6*s->net->Pw[i][j].x;
                Rvv.y += temp_6*s->net->Pw[i][j].y;
                Rvv.z += temp_6*s->net->Pw[i][j].z;
            }
        }
    
        free(dN_tab_u);
        free(dN_tab_v);
        free(ddN_tab_u);
        free(ddN_tab_v);
        free_tab_2d(N_tab_u, n+p+1);
        free_tab_2d(N_tab_v, m+q+1);

        // VECTOR S = {0.0,0.0,0.0};
        VECTOR Su = {0.0,0.0,0.0};
        VECTOR Sv = {0.0,0.0,0.0};
        VECTOR Suv = {0.0,0.0,0.0};
        VECTOR Suu = {0.0,0.0,0.0};
        VECTOR Svv = {0.0,0.0,0.0};

        // printf("D = %f\n", D);

        S = v_mult_scal(R, 1.0/D);
        Su = v_mult_scal(v_sub(Ru,v_mult_scal(S,Du)),1.0/D);
        Sv = v_mult_scal(v_sub(Rv,v_mult_scal(S,Dv)),1.0/D);
        Suv.x = (Ruv.x - Duv*S.x - Du*Sv.x - Dv*Su.x)/D;
        Suv.y = (Ruv.y - Duv*S.y - Du*Sv.y - Dv*Su.y)/D;
        Suv.z = (Ruv.z - Duv*S.z - Du*Sv.z - Dv*Su.z)/D;

        Suu.x = (Ruu.x - 2*Du*Su.x - Duu*S.x)/D;
        Suu.y = (Ruu.y - 2*Du*Su.y - Duu*S.y)/D;
        Suu.z = (Ruu.z - 2*Du*Su.z - Duu*S.z)/D;

        Svv.x = (Rvv.x - 2*Dv*Sv.x - Dvv*S.x)/D;
        Svv.y = (Rvv.y - 2*Dv*Sv.y - Dvv*S.y)/D;
        Svv.z = (Rvv.z - 2*Dv*Sv.z - Dvv*S.z)/D;

        VECTOR r = v_sub(S,P);
        float f = prod_scal(r, Su);
        float g = prod_scal(r, Sv);
        float fu = norm_vector(Su)*norm_vector(Su) + prod_scal(r,Suu);
        float fv = prod_scal(Su, Sv) + prod_scal(r,Suv);
        float gu = prod_scal(Su, Sv) + prod_scal(r, Suv);
        float gv = norm_vector(Sv)*norm_vector(Sv) + prod_scal(r, Svv);    

        float det = fu*gv-fv*gu;

        float dui = (g*fv-f*gv)/det;
        float dvi = (f*gu-g*fu)/det;

        // printf("det = %f\n", det);
        float nu = u + dui;
        float nv = v + dvi;
        
        if (nu < 0){nu = 0.0;}
        if (nu >= 1){nu = 0.9999;}
        if (nv < 0){nv = 0.0;}
        if (nv >= 1){nv = 0.9999;}
        

        if (u == nu && v == nv){
            pthread_mutex_lock(&verrou);
            Stats_nurbs->nb_points ++;
            Stats_nurbs->nb_iterations += iterations + 1;
            pthread_mutex_unlock(&verrou);
            return S;
        }



        u = nu;
        v = nv;

        // printf("u = %f | v = %f \n", u,v);
        // printf("S : %f | %f | %f \n", S.x, S.y, S.z);
    }

    // printf("S final : %f | %f | %f \n", S.x, S.y, S.z);
    pthread_mutex_lock(&verrou);
    Stats_nurbs->nb_points ++;
    Stats_nurbs->nb_iterations += 40;
    pthread_mutex_unlock(&verrou);
    return S;
}

// Prog dyn
VECTOR projection_nurbs_2(SURFACE s, VECTOR P){
    VECTOR Q_1 = projection_nurbs_aux_2(s, P, 0.0, 0.0);
    VECTOR Q_2 = projection_nurbs_aux_2(s, P, 0.999, 0.0);
    VECTOR Q_3 = projection_nurbs_aux_2(s, P, 0.0, 0.999);
    VECTOR Q_4 = projection_nurbs_aux_2(s, P, 0.999, 0.999);

    // printf("Q1 : %f | %f | %f \n", Q_1.x, Q_1.y, Q_1.z);
    // printf("Q2 : %f | %f | %f \n", Q_2.x, Q_2.y, Q_2.z);
    // printf("Q3 : %f | %f | %f \n", Q_3.x, Q_3.y, Q_3.z);
    // printf("Q4 : %f | %f | %f \n", Q_4.x, Q_4.y, Q_4.z);

    float d_1 = dist_2_pts(P, Q_1);
    float d_2 = dist_2_pts(P, Q_2);
    float d_3 = dist_2_pts(P, Q_3);
    float d_4 = dist_2_pts(P, Q_4);

    float d = fmin(fmin(d_1, d_2), fmin(d_3, d_4));

    if (d_1 == d){return Q_1;}
    if (d_2 == d){return Q_2;}
    if (d_3 == d){return Q_3;}
    return Q_4;
}



// Prog dyn
float** N_nurbs_tab(KNOTVECTOR knot, float u, int n, int p){ 
    // float m = n + p;
    float** tab = create_2d_tab(n+p+1, p+1, 0.0);
    
    for (int i = 0; i < n+p+1; i++){
        if ((knot->U[i] <= u) && (u < knot->U[i+1])){
            tab[i][0] = 1.0;
        } else {
            tab[i][0] = 0.0;
        }
    }
    

    for (int j = 1; j < p + 1; j++){
        for (int i = 0; i < n+p+1; i++){
            // printf("%d-%d\n", i,j);
            if (i + j > p + n){
                tab[i][j] = 0.0;
            }
            else {
                float t1, t2;
                if (knot->U[i+j] - knot->U[i] == 0){
                    t1 = 0.0;
                } else {
                    t1 = (u - knot->U[i])/(knot->U[i+j] - knot->U[i]);
                }
                // assert(i+j+1 < knot->m);
                if (knot->U[i+j+1] - knot->U[i+1] == 0){
                    t2 = 0.0;
                } else {
                    t2 = (knot->U[i+j+1] - u)/(knot->U[i+j+1] - knot->U[i+1]);
                }

                tab[i][j] = t1*tab[i][j-1] + t2*tab[i+1][j-1];
            }   
        }
    }
    
    return tab;
}

float* dN_nurbs_tab(KNOTVECTOR knot, float u, int n, int p, float** N_tab){ 
    float* tab = malloc((n+1)*sizeof(float));

    
    for (int i = 0; i < n+1; i++){
        float t1, t2;
        if (knot->U[i+p] - knot->U[i] == 0){
            t1 = 0.0;
        } else {
            t1 = (p)/(knot->U[i+p] - knot->U[i]);
        }

        if (knot->U[i+p+1] - knot->U[i+1] == 0){
            t2 = 0.0;
        } else {
            t2 = (p)/(knot->U[i+p+1] - knot->U[i+1]);
        }
        
        tab[i] = t1*N_tab[i][p-1] - t2*N_tab[i+1][p-1]; // N'_i_p
    }
        
    return tab;
}

float* ddN_nurbs_tab(KNOTVECTOR knot, float u, int n, int p, float** N_tab){ 
    float* tab = malloc((n+1)*sizeof(float));
    for (int i = 0; i < n+1; i++){
        float t1, t2, t3, t4, t5, t6;
        float T1, T2;
        
        if (knot->U[i+p] - knot->U[i] == 0){
            t1 = 0.0;
        } else {
            t1 = (p)/(knot->U[i+p] - knot->U[i]);
        }

        if (t1 == 0){
            T1 = 0;
        } else {
            if (knot->U[i+p-1] - knot->U[i] == 0){
                t3 = 0;
            } else {
                t3 = (p-1)/(knot->U[i+p-1] - knot->U[i]);
            }
            if (knot->U[i+p] - knot->U[i+1] == 0){
                t4 = 0;
            } else {
                t4 = (p-1)/(knot->U[i+p] - knot->U[i+1]);
            }
            T1 = t1*(t3*N_tab[i][p-2] - t4*N_tab[i+1][p-2]);
        }

        if (knot->U[i+p+1] - knot->U[i+1] == 0){
            t2 = 0.0;
        } else {
            t2 = (p)/(knot->U[i+p+1] - knot->U[i+1]);
        }
        
        if (t2 == 0){
            T2 = 0;
        } else {
            if (knot->U[i+p] - knot->U[i+1] == 0){
                t5 = 0;
            } else {
                t5 = (p-1)/(knot->U[i+p] - knot->U[i+1]);
            }
            if (knot->U[i+p+1] - knot->U[i+2] == 0){
                t6 = 0;
            } else {
                t6 = (p-1)/(knot->U[i+p+1] - knot->U[i+2]);
            }
            T2 = t2*(t5*N_tab[i+1][p-2] - t6*N_tab[i+2][p-2]);
        }

        tab[i] = T1 - T2;
    }
    return tab;
}



// Prog dyn division du la nurbs, point centre
VECTOR projection_nurbs_aux_3(SURFACE s, VECTOR P, float a, float b, float c, float d, int max_it){
    int p = s->p; int q = s->q; int n = s->net->n; int m = s->net->m;
    float u = (a + b)/2.0;
    float v = (c + d)/2.0;
    VECTOR S;
        
    for (int iterations = 0; iterations < max_it; iterations++){
        float** N_tab_u = N_nurbs_tab(s->knu, u, n, p);
        float** N_tab_v = N_nurbs_tab(s->knv, v, m, q);

        float* dN_tab_u = dN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* dN_tab_v = dN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        float* ddN_tab_u = ddN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* ddN_tab_v = ddN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        // Calcule de R et D
        VECTOR R = {0.0,0.0,0.0};
        VECTOR Ru = {0.0,0.0,0.0};
        VECTOR Rv = {0.0,0.0,0.0};
        VECTOR Ruv = {0.0,0.0,0.0};
        VECTOR Ruu = {0.0,0.0,0.0};
        VECTOR Rvv = {0.0,0.0,0.0};

        float D = 0.0;
        float Du = 0.0;
        float Dv = 0.0;
        float Duv = 0.0;
        float Duu = 0.0;
        float Dvv = 0.0;

        // Calcule des R et D pour les S
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                // R et D
                float temp_1 = N_tab_u[i][p]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                D += temp_1;
                R.x += temp_1*s->net->Pw[i][j].x;
                R.y += temp_1*s->net->Pw[i][j].y;
                R.z += temp_1*s->net->Pw[i][j].z;

                // Ru et Du
                float temp_2 = dN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Du += temp_2;
                Ru.x += temp_2*s->net->Pw[i][j].x;
                Ru.y += temp_2*s->net->Pw[i][j].y;
                Ru.z += temp_2*s->net->Pw[i][j].z;

                // Rv et Dv
                float temp_3 = N_tab_u[i][p]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Dv += temp_3;
                Rv.x += temp_3*s->net->Pw[i][j].x;
                Rv.y += temp_3*s->net->Pw[i][j].y;
                Rv.z += temp_3*s->net->Pw[i][j].z;

                // Ruv et Duv
                float temp_4 = dN_tab_u[i]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Duv += temp_4;
                Ruv.x += temp_4*s->net->Pw[i][j].x;
                Ruv.y += temp_4*s->net->Pw[i][j].y;
                Ruv.z += temp_4*s->net->Pw[i][j].z;

                // Ruu et Duu
                float temp_5 = ddN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Duu += temp_5;
                Ruu.x += temp_5*s->net->Pw[i][j].x;
                Ruu.y += temp_5*s->net->Pw[i][j].y;
                Ruu.z += temp_5*s->net->Pw[i][j].z;

                // Rvv et Dvv
                float temp_6 = N_tab_u[i][p]*ddN_tab_v[j]*s->net->Pw[i][j].w;
                Dvv += temp_6;
                Rvv.x += temp_6*s->net->Pw[i][j].x;
                Rvv.y += temp_6*s->net->Pw[i][j].y;
                Rvv.z += temp_6*s->net->Pw[i][j].z;
            }
        }
    
        free(dN_tab_u);
        free(dN_tab_v);
        free(ddN_tab_u);
        free(ddN_tab_v);
        free_tab_2d(N_tab_u, n+p+1);
        free_tab_2d(N_tab_v, m+q+1);

        // VECTOR S = {0.0,0.0,0.0};
        VECTOR Su = {0.0,0.0,0.0};
        VECTOR Sv = {0.0,0.0,0.0};
        VECTOR Suv = {0.0,0.0,0.0};
        VECTOR Suu = {0.0,0.0,0.0};
        VECTOR Svv = {0.0,0.0,0.0};

        // printf("D = %f\n", D);

        S = v_mult_scal(R, 1.0/D);
        Su = v_mult_scal(v_sub(Ru,v_mult_scal(S,Du)),1.0/D);
        Sv = v_mult_scal(v_sub(Rv,v_mult_scal(S,Dv)),1.0/D);
        Suv.x = (Ruv.x - Duv*S.x - Du*Sv.x - Dv*Su.x)/D;
        Suv.y = (Ruv.y - Duv*S.y - Du*Sv.y - Dv*Su.y)/D;
        Suv.z = (Ruv.z - Duv*S.z - Du*Sv.z - Dv*Su.z)/D;

        Suu.x = (Ruu.x - 2*Du*Su.x - Duu*S.x)/D;
        Suu.y = (Ruu.y - 2*Du*Su.y - Duu*S.y)/D;
        Suu.z = (Ruu.z - 2*Du*Su.z - Duu*S.z)/D;

        Svv.x = (Rvv.x - 2*Dv*Sv.x - Dvv*S.x)/D;
        Svv.y = (Rvv.y - 2*Dv*Sv.y - Dvv*S.y)/D;
        Svv.z = (Rvv.z - 2*Dv*Sv.z - Dvv*S.z)/D;

        VECTOR r = v_sub(S,P);
        float f = prod_scal(r, Su);
        float g = prod_scal(r, Sv);
        float fu = norm_vector(Su)*norm_vector(Su) + prod_scal(r,Suu);
        float fv = prod_scal(Su, Sv) + prod_scal(r,Suv);
        float gu = prod_scal(Su, Sv) + prod_scal(r, Suv);
        float gv = norm_vector(Sv)*norm_vector(Sv) + prod_scal(r, Svv);    

        float det = fu*gv-fv*gu;

        float dui = (g*fv-f*gv)/det;
        float dvi = (f*gu-g*fu)/det;

        // printf("det = %f\n", det);
        float nu = u + dui;
        float nv = v + dvi;
        
        if (nu < a){nu = a;}
        if (nu >= b){nu = b - 0.0001;}
        if (nv < c){nv = c;}
        if (nv >= d){nv = d - 0.0001;}
        

        // float c1 = fabs(f/(norm_vector(Su)*norm_vector(r)));
        // float c2 = fabs(g/(norm_vector(Sv)*norm_vector(r)));

        // if (c1 <= EPSILON_CRIT_NURBS && c2 <= EPSILON_CRIT_NURBS){
        //     pthread_mutex_lock(&verrou);
        //     Stats_nurbs->nb_points ++;
        //     Stats_nurbs->nb_iterations += iterations + 1;
        //     pthread_mutex_unlock(&verrou);
        //     return S;
        // }
        

        if (u == nu && v == nv){
            pthread_mutex_lock(&verrou);
            Stats_nurbs->nb_points ++;
            Stats_nurbs->nb_iterations += iterations + 1;
            pthread_mutex_unlock(&verrou);
            return S;
        }



        u = nu;
        v = nv;

        // printf("u = %f | v = %f \n", u,v);
        // printf("S : %f | %f | %f \n", S.x, S.y, S.z);
    }

    // printf("S final : %f | %f | %f \n", S.x, S.y, S.z);
    // printf("S final : %f | %f | %f \n", S.x, S.y, S.z);
    pthread_mutex_lock(&verrou);
    Stats_nurbs->nb_points ++;
    Stats_nurbs->nb_iterations += max_it;
    pthread_mutex_unlock(&verrou);
    return S;
}


// Prog dyn recursif
VECTOR projection_nurbs_3(SURFACE s, VECTOR P, float a, float b, float c, float d, int k, int max_it){
    

    if (k == 0){
        return projection_nurbs_aux_3(s, P, a, b, c, d, max_it);
    } else {
        VECTOR Q_1 = projection_nurbs_3(s, P, a, (a+b)/2.0, c, (c+d)/2.0, k-1, max_it);
        VECTOR Q_2 = projection_nurbs_3(s, P, (a+b)/2.0, b, c, (c+d)/2.0, k-1, max_it);
        VECTOR Q_3 = projection_nurbs_3(s, P, a, (a+b)/2.0, (c+d)/2.0, d, k-1, max_it);
        VECTOR Q_4 = projection_nurbs_3(s, P, (a+b)/2.0, b, (c+d)/2.0, d, k-1, max_it);

        float d_1 = dist_2_pts(P, Q_1);
        float d_2 = dist_2_pts(P, Q_2);
        float d_3 = dist_2_pts(P, Q_3);
        float d_4 = dist_2_pts(P, Q_4);
        float d = fmin(fmin(d_1, d_2), fmin(d_3, d_4));

        if (d_1 == d){return Q_1;}
        if (d_2 == d){return Q_2;}
        if (d_3 == d){return Q_3;}
        return Q_4;
    }
}


// Methode Quasi Newton + Recursif
VECTOR projection_nurbs_aux_4(SURFACE s, VECTOR P, float a, float b, float c, float d, int max_it){
    int p = s->p; int q = s->q; int n = s->net->n; int m = s->net->m;
    float u = (a + b)/2.0;
    float v = (c + d)/2.0;
    VECTOR S;
        
    for (int iterations = 0; iterations < max_it; iterations++){
        float** N_tab_u = N_nurbs_tab(s->knu, u, n, p);
        float** N_tab_v = N_nurbs_tab(s->knv, v, m, q);

        float* dN_tab_u = dN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* dN_tab_v = dN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        float* ddN_tab_u = ddN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* ddN_tab_v = ddN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        // Calcule de R et D
        VECTOR R = {0.0,0.0,0.0};
        VECTOR Ru = {0.0,0.0,0.0};
        VECTOR Rv = {0.0,0.0,0.0};
        VECTOR Ruv = {0.0,0.0,0.0};
        VECTOR Ruu = {0.0,0.0,0.0};
        VECTOR Rvv = {0.0,0.0,0.0};

        float D = 0.0;
        float Du = 0.0;
        float Dv = 0.0;
        float Duv = 0.0;
        float Duu = 0.0;
        float Dvv = 0.0;

        // Calcule des R et D pour les S
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                // R et D
                float temp_1 = N_tab_u[i][p]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                D += temp_1;
                R.x += temp_1*s->net->Pw[i][j].x;
                R.y += temp_1*s->net->Pw[i][j].y;
                R.z += temp_1*s->net->Pw[i][j].z;

                // Ru et Du
                float temp_2 = dN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Du += temp_2;
                Ru.x += temp_2*s->net->Pw[i][j].x;
                Ru.y += temp_2*s->net->Pw[i][j].y;
                Ru.z += temp_2*s->net->Pw[i][j].z;

                // Rv et Dv
                float temp_3 = N_tab_u[i][p]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Dv += temp_3;
                Rv.x += temp_3*s->net->Pw[i][j].x;
                Rv.y += temp_3*s->net->Pw[i][j].y;
                Rv.z += temp_3*s->net->Pw[i][j].z;

                // Ruv et Duv
                float temp_4 = dN_tab_u[i]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Duv += temp_4;
                Ruv.x += temp_4*s->net->Pw[i][j].x;
                Ruv.y += temp_4*s->net->Pw[i][j].y;
                Ruv.z += temp_4*s->net->Pw[i][j].z;

                // Ruu et Duu
                float temp_5 = ddN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Duu += temp_5;
                Ruu.x += temp_5*s->net->Pw[i][j].x;
                Ruu.y += temp_5*s->net->Pw[i][j].y;
                Ruu.z += temp_5*s->net->Pw[i][j].z;

                // Rvv et Dvv
                float temp_6 = N_tab_u[i][p]*ddN_tab_v[j]*s->net->Pw[i][j].w;
                Dvv += temp_6;
                Rvv.x += temp_6*s->net->Pw[i][j].x;
                Rvv.y += temp_6*s->net->Pw[i][j].y;
                Rvv.z += temp_6*s->net->Pw[i][j].z;
            }
        }
    
        free(dN_tab_u);
        free(dN_tab_v);
        free(ddN_tab_u);
        free(ddN_tab_v);
        free_tab_2d(N_tab_u, n+p+1);
        free_tab_2d(N_tab_v, m+q+1);

        // VECTOR S = {0.0,0.0,0.0};
        VECTOR Su = {0.0,0.0,0.0};
        VECTOR Sv = {0.0,0.0,0.0};
        VECTOR Suv = {0.0,0.0,0.0};
        VECTOR Suu = {0.0,0.0,0.0};
        VECTOR Svv = {0.0,0.0,0.0};

        // printf("D = %f\n", D);

        S = v_mult_scal(R, 1.0/D);
        Su = v_mult_scal(v_sub(Ru,v_mult_scal(S,Du)),1.0/D);
        Sv = v_mult_scal(v_sub(Rv,v_mult_scal(S,Dv)),1.0/D);
        Suv.x = (Ruv.x - Duv*S.x - Du*Sv.x - Dv*Su.x)/D;
        Suv.y = (Ruv.y - Duv*S.y - Du*Sv.y - Dv*Su.y)/D;
        Suv.z = (Ruv.z - Duv*S.z - Du*Sv.z - Dv*Su.z)/D;

        Suu.x = (Ruu.x - 2*Du*Su.x - Duu*S.x)/D;
        Suu.y = (Ruu.y - 2*Du*Su.y - Duu*S.y)/D;
        Suu.z = (Ruu.z - 2*Du*Su.z - Duu*S.z)/D;

        Svv.x = (Rvv.x - 2*Dv*Sv.x - Dvv*S.x)/D;
        Svv.y = (Rvv.y - 2*Dv*Sv.y - Dvv*S.y)/D;
        Svv.z = (Rvv.z - 2*Dv*Sv.z - Dvv*S.z)/D;

        VECTOR r = v_sub(S,P);
        // float f = prod_scal(r, Su);
        // float g = prod_scal(r, Sv);
        // float fu = norm_vector(Su)*norm_vector(Su) + prod_scal(r,Suu);
        // float fv = prod_scal(Su, Sv) + prod_scal(r,Suv);
        // float gu = prod_scal(Su, Sv) + prod_scal(r, Suv);
        // float gv = norm_vector(Sv)*norm_vector(Sv) + prod_scal(r, Svv);    

        // float det = fu*gv-fv*gu;

        // float dui = (g*fv-f*gv)/det;
        // float dvi = (f*gu-g*fu)/det;

        float f = norm_vector(r);
        if (f == 0){
            pthread_mutex_lock(&verrou);
            Stats_nurbs->nb_points ++;
            Stats_nurbs->nb_iterations += iterations + 1;
            pthread_mutex_unlock(&verrou);
            return S;
        }
        
        float fu = prod_scal(Su, r)/f;
        float fv = prod_scal(Sv, r)/f;
        float fuu = (prod_scal(Suu, r) + prod_scal(Su, Su))/f - prod_scal(Su, r)*fu/(f*f);
        float fvv = (prod_scal(Svv, r) + prod_scal(Sv, Sv))/f - prod_scal(Sv, r)*fv/(f*f);
        float fuv = (prod_scal(Suv, r) + prod_scal(Su, Sv))/f - (prod_scal(Su, r)*fv)/(f*f);

        float det = fuv*fuv - fuu*fvv;
        
        float nu = u + (fu*fvv - fv*fuv)/det;
        float nv = v + (fv*fuu - fu*fuv)/det;

        // printf("det = %f\n", det);
        // float nu = u + dui;
        // float nv = v + dvi;
        
        if (nu < a){nu = a;}
        if (nu >= b){nu = b - 0.0001;}
        if (nv < c){nv = c;}
        if (nv >= d){nv = d - 0.0001;}
        

        // float c1 = fabs(f/(norm_vector(Su)*norm_vector(r)));
        // float c2 = fabs(g/(norm_vector(Sv)*norm_vector(r)));

        // if (c1 <= EPSILON_CRIT_NURBS && c2 <= EPSILON_CRIT_NURBS){
        //     pthread_mutex_lock(&verrou);
        //     Stats_nurbs->nb_points ++;
        //     Stats_nurbs->nb_iterations += iterations + 1;
        //     pthread_mutex_unlock(&verrou);
        //     return S;
        // }
        

        if (u == nu && v == nv){
            pthread_mutex_lock(&verrou);
            Stats_nurbs->nb_points ++;
            Stats_nurbs->nb_iterations += iterations + 1;
            pthread_mutex_unlock(&verrou);
            return S;
        }



        u = nu;
        v = nv;

        // printf("u = %f | v = %f \n", u,v);
        // printf("S : %f | %f | %f \n", S.x, S.y, S.z);
    }

    // printf("S final : %f | %f | %f \n", S.x, S.y, S.z);
    pthread_mutex_lock(&verrou);
    Stats_nurbs->nb_points ++;
    Stats_nurbs->nb_iterations += max_it;
    pthread_mutex_unlock(&verrou);
    return S;
}


VECTOR S_nurbs_2(SURFACE s, float u, float v){
    int p = s->p; int q = s->q; int n = s->net->n; int m = s->net->m;
    float** N_tab_u = N_nurbs_tab(s->knu, u, n, p);
    float** N_tab_v = N_nurbs_tab(s->knv, v, m, q);
    // Calcule des R et D pour les S

    VECTOR R = {0.0,0.0,0.0};
    float D = 0.0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            
            // R et D
            float temp_1 = N_tab_u[i][p]*N_tab_v[j][q]*s->net->Pw[i][j].w;
            D += temp_1;
            R.x += temp_1*s->net->Pw[i][j].x;
            R.y += temp_1*s->net->Pw[i][j].y;
            R.z += temp_1*s->net->Pw[i][j].z;
        }
    }
    free_tab_2d(N_tab_u, n+p+1);
    free_tab_2d(N_tab_v, m+q+1);

    VECTOR S = v_mult_scal(R, 1.0/D);

    return S;
}


// Methode Quasi Newton + Recursif
VECTOR projection_nurbs_4(SURFACE s, VECTOR P, float a, float b, float c, float d, int k, int max_it){
    if (k == 0){
        return projection_nurbs_aux_4(s, P, a, b, c, d, max_it);
    } else {
        VECTOR Q_1 = projection_nurbs_4(s, P, a, (a+b)/2.0, c, (c+d)/2.0, k-1, max_it);
        VECTOR Q_2 = projection_nurbs_4(s, P, (a+b)/2.0, b, c, (c+d)/2.0, k-1, max_it);
        VECTOR Q_3 = projection_nurbs_4(s, P, a, (a+b)/2.0, (c+d)/2.0, d, k-1, max_it);
        VECTOR Q_4 = projection_nurbs_4(s, P, (a+b)/2.0, b, (c+d)/2.0, d, k-1, max_it);

        float d_1 = dist_2_pts(P, Q_1);
        float d_2 = dist_2_pts(P, Q_2);
        float d_3 = dist_2_pts(P, Q_3);
        float d_4 = dist_2_pts(P, Q_4);
        float d = fmin(fmin(d_1, d_2), fmin(d_3, d_4));

        if (d_1 == d){return Q_1;}
        if (d_2 == d){return Q_2;}
        if (d_3 == d){return Q_3;}
        return Q_4;
    }
}


VECTOR projection_nurbs_aux_5(SURFACE s, VECTOR P, float a, float b, float c, float d, int max_it){
    int p = s->p; int q = s->q; int n = s->net->n; int m = s->net->m;
    float u = (a + b)/2.0;
    float v = (c + d)/2.0;
    VECTOR S;

    VECTOR P_proj = S_nurbs_2(s, u, v);
        
    for (int iterations = 0; iterations < max_it; iterations++){
        float** N_tab_u = N_nurbs_tab(s->knu, u, n, p);
        float** N_tab_v = N_nurbs_tab(s->knv, v, m, q);

        float* dN_tab_u = dN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* dN_tab_v = dN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        float* ddN_tab_u = ddN_nurbs_tab(s->knu, u, n, p, N_tab_u);
        float* ddN_tab_v = ddN_nurbs_tab(s->knv, v, m, q, N_tab_v);

        // Calcule de R et D
        VECTOR R = {0.0,0.0,0.0};
        VECTOR Ru = {0.0,0.0,0.0};
        VECTOR Rv = {0.0,0.0,0.0};
        VECTOR Ruv = {0.0,0.0,0.0};
        VECTOR Ruu = {0.0,0.0,0.0};
        VECTOR Rvv = {0.0,0.0,0.0};

        float D = 0.0;
        float Du = 0.0;
        float Dv = 0.0;
        float Duv = 0.0;
        float Duu = 0.0;
        float Dvv = 0.0;

        // Calcule des R et D pour les S
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                // R et D
                float temp_1 = N_tab_u[i][p]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                D += temp_1;
                R.x += temp_1*s->net->Pw[i][j].x;
                R.y += temp_1*s->net->Pw[i][j].y;
                R.z += temp_1*s->net->Pw[i][j].z;

                // Ru et Du
                float temp_2 = dN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Du += temp_2;
                Ru.x += temp_2*s->net->Pw[i][j].x;
                Ru.y += temp_2*s->net->Pw[i][j].y;
                Ru.z += temp_2*s->net->Pw[i][j].z;

                // Rv et Dv
                float temp_3 = N_tab_u[i][p]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Dv += temp_3;
                Rv.x += temp_3*s->net->Pw[i][j].x;
                Rv.y += temp_3*s->net->Pw[i][j].y;
                Rv.z += temp_3*s->net->Pw[i][j].z;

                // Ruv et Duv
                float temp_4 = dN_tab_u[i]*dN_tab_v[j]*s->net->Pw[i][j].w;
                Duv += temp_4;
                Ruv.x += temp_4*s->net->Pw[i][j].x;
                Ruv.y += temp_4*s->net->Pw[i][j].y;
                Ruv.z += temp_4*s->net->Pw[i][j].z;

                // Ruu et Duu
                float temp_5 = ddN_tab_u[i]*N_tab_v[j][q]*s->net->Pw[i][j].w;
                Duu += temp_5;
                Ruu.x += temp_5*s->net->Pw[i][j].x;
                Ruu.y += temp_5*s->net->Pw[i][j].y;
                Ruu.z += temp_5*s->net->Pw[i][j].z;

                // Rvv et Dvv
                float temp_6 = N_tab_u[i][p]*ddN_tab_v[j]*s->net->Pw[i][j].w;
                Dvv += temp_6;
                Rvv.x += temp_6*s->net->Pw[i][j].x;
                Rvv.y += temp_6*s->net->Pw[i][j].y;
                Rvv.z += temp_6*s->net->Pw[i][j].z;
            }
        }
    
        free(dN_tab_u);
        free(dN_tab_v);
        free(ddN_tab_u);
        free(ddN_tab_v);
        free_tab_2d(N_tab_u, n+p+1);
        free_tab_2d(N_tab_v, m+q+1);

        // VECTOR S = {0.0,0.0,0.0};
        VECTOR Su = {0.0,0.0,0.0};
        VECTOR Sv = {0.0,0.0,0.0};
        VECTOR Suv = {0.0,0.0,0.0};
        VECTOR Suu = {0.0,0.0,0.0};
        VECTOR Svv = {0.0,0.0,0.0};

        // printf("D = %f\n", D);

        S = v_mult_scal(R, 1.0/D);
        Su = v_mult_scal(v_sub(Ru,v_mult_scal(S,Du)),1.0/D);
        Sv = v_mult_scal(v_sub(Rv,v_mult_scal(S,Dv)),1.0/D);
        Suv.x = (Ruv.x - Duv*S.x - Du*Sv.x - Dv*Su.x)/D;
        Suv.y = (Ruv.y - Duv*S.y - Du*Sv.y - Dv*Su.y)/D;
        Suv.z = (Ruv.z - Duv*S.z - Du*Sv.z - Dv*Su.z)/D;

        Suu.x = (Ruu.x - 2*Du*Su.x - Duu*S.x)/D;
        Suu.y = (Ruu.y - 2*Du*Su.y - Duu*S.y)/D;
        Suu.z = (Ruu.z - 2*Du*Su.z - Duu*S.z)/D;

        Svv.x = (Rvv.x - 2*Dv*Sv.x - Dvv*S.x)/D;
        Svv.y = (Rvv.y - 2*Dv*Sv.y - Dvv*S.y)/D;
        Svv.z = (Rvv.z - 2*Dv*Sv.z - Dvv*S.z)/D;



        VECTOR normal = normalise_vecteur(prod_vect(Su, Sv));

        float mat[9];
        mat[0] = Su.x; mat[1] = Sv.x; mat[2] = normal.x;
        mat[3] = Su.y; mat[4] = Sv.y; mat[5] = normal.y;
        mat[6] = Su.z; mat[7] = Sv.z; mat[8] = normal.z;

        // return M^-1 * X
        VECTOR lambda = inv_mat_3_x_vect(mat, v_sub(P, P_proj));

        float lambda_1 = lambda.x;
        float lambda_2 = lambda.y;
        

        // c'(0)
        VECTOR cp0 = v_add(v_mult_scal(Su,lambda_1),v_mult_scal(Sv,lambda_2));

        float g11 = prod_scal(Su, Su);
        float g12 = prod_scal(Su, Sv);
        float g21 = prod_scal(Sv, Su);
        float g22 = prod_scal(Sv, Sv);

        float h11 = prod_scal(Suu, normal);
        float h12 = prod_scal(Suv, normal);
        float h21 = h12;
        float h22 = prod_scal(Svv, normal);

        float kn1 = h11*lambda_1*lambda_1 + h12*lambda_1*lambda_2 + h21*lambda_2*lambda_1 + h22*lambda_2*lambda_2;
        float kn2 = g11*lambda_1*lambda_1 + g12*lambda_1*lambda_2 + g21*lambda_2*lambda_1 + g22*lambda_2*lambda_2;
        float kn = (kn1/kn2);

        // Center of the curve
        VECTOR C = v_add(P_proj, v_mult_scal(normal, 1.0/kn));
        // kn = fabs(kn);
        float ray = fabs(1.0/kn);
        VECTOR q = v_mult_scal(normalise_vecteur(v_sub(P, P_proj)), ray);

        // Delta t^2 = 2/kn * ||c'(0) x q-P_0 || / || c'(0) ||^3
        float t2 = (2.0*ray)*norm_vector(prod_vect(cp0, v_sub(q,P_proj)))*1.0/(norm_vector(cp0)*norm_vector(cp0)*norm_vector(cp0));

        // Signe of Delta t
        float t;
        if (prod_scal(cp0, v_sub(q, P_proj)) > 0){
            t = sqrt(t2);
        } else {
            t = -sqrt(t2);
        }
        
        float nu = u + lambda_1*t;
        float nv = v + lambda_2*t;

        // If nu && nv aren't valid arguments
        if (nu < a){nu = a;}
        if (nu >= b){nu = b - 0.0001;}
        if (nv < c){nv = c;}
        if (nv >= d){nv = d - 0.0001;}        

        if (u == nu && v == nv){
            pthread_mutex_lock(&verrou);
            Stats_nurbs->nb_points ++;
            Stats_nurbs->nb_iterations += iterations + 1;
            pthread_mutex_unlock(&verrou);
            return S;
        }

        u = nu;
        v = nv;
        P_proj = S_nurbs_2(s, u, v);


        // printf("\n");
        // printf("l1 : %f | l2 : %f\n", lambda_1, lambda_2);
        // printf("Su : %f | %f | %f\n", Su.x, Su.y, Su.z);
        // printf("Sv : %f | %f | %f\n", Sv.x, Sv.y, Sv.z);
        // printf("n : %f | %f | %f\n", normal.x, normal.y, normal.z);
        // printf("kn : %f\n", kn);
        // printf("u : %f | v : %f | nu : %f | nv : %f \n", u, v, nu, nv);
        // printf("P : %f |%f |%f \n", P_proj.x, P_proj.y, P_proj.z);

    }
    pthread_mutex_lock(&verrou);
    Stats_nurbs->nb_points ++;
    Stats_nurbs->nb_iterations += max_it + 1;
    pthread_mutex_unlock(&verrou);
    return S;
}



VECTOR projection_nurbs_5(SURFACE s, VECTOR P, float a, float b, float c, float d, int k, int max_it){
    if (k == 0){
        return projection_nurbs_aux_5(s, P, a, b, c, d, max_it);
    } else {
        VECTOR Q_1 = projection_nurbs_5(s, P, a, (a+b)/2.0, c, (c+d)/2.0, k-1, max_it);
        VECTOR Q_2 = projection_nurbs_5(s, P, (a+b)/2.0, b, c, (c+d)/2.0, k-1, max_it);
        VECTOR Q_3 = projection_nurbs_5(s, P, a, (a+b)/2.0, (c+d)/2.0, d, k-1, max_it);
        VECTOR Q_4 = projection_nurbs_5(s, P, (a+b)/2.0, b, (c+d)/2.0, d, k-1, max_it);

        float d_1 = dist_2_pts(P, Q_1);
        float d_2 = dist_2_pts(P, Q_2);
        float d_3 = dist_2_pts(P, Q_3);
        float d_4 = dist_2_pts(P, Q_4);
        float d = fmin(fmin(d_1, d_2), fmin(d_3, d_4));

        if (d_1 == d){return Q_1;}
        if (d_2 == d){return Q_2;}
        if (d_3 == d){return Q_3;}
        return Q_4;
    }
}