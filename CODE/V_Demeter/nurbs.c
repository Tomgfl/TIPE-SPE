#include "nurbs.h"


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
    SURFACE res = create_surface(2,2);

    CNET net = create_cnet(5,5);
    net->Pw[0][0] = (CPOINT){-6,-3.8,0,1};
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

    KNOTVECTOR knu = create_knotvector(8);
    knu->U[0] = 0;
    knu->U[1] = 0;
    knu->U[2] = 0;
    knu->U[3] = 1.0/3.0;
    knu->U[4] = 2.0/3.0;
    knu->U[5] = 1;
    knu->U[6] = 1;
    knu->U[7] = 1;
    res->knu = knu;

    KNOTVECTOR knv = create_knotvector(8);
    knv->U[0] = 0;
    knv->U[1] = 0;
    knv->U[2] = 0;
    knv->U[3] = 1.0/3.0;
    knv->U[4] = 2.0/3.0;
    knv->U[5] = 1;
    knu->U[6] = 1;
    knu->U[7] = 1;

    res->knv = knv;
    return res;
}


// SURFACE nurbs_3(){
//     SURFACE res = create_surface(4,4);

//     CNET net = create_cnet(13,13);
//     net->Pw[][] = (CPOINT){,,,};
// }


// Fonction de base Nij associer a U
float N_nurbs(int i, int p, float u, KNOTVECTOR U){
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



// ### V1 - (pas opti) ### //
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

bool crit_1(float u, float v, SURFACE s, VECTOR P){
    if (norm_vector(r_nurbs(u, v, s, P)) <= EPS_1){
        return true;
    }
    return false;
}

bool crit_2(float u, float v, SURFACE s, VECTOR P){
    if ((fabs(prod_scal(S_u_nurbs(u, v, s),r_nurbs(u, v, s, P))))/(norm_vector(S_u_nurbs(u, v, s))*norm_vector(r_nurbs(u, v, s, P))) <= EPS_2){
        if ((fabs(prod_scal(S_v_nurbs(u, v, s),r_nurbs(u, v, s, P))))/(norm_vector(S_v_nurbs(u, v, s))*norm_vector(r_nurbs(u, v, s, P))) <= EPS_2){
            return true;
        }
    }
    return false;
}


VECTOR projection_nurbs_aux(SURFACE s, VECTOR P, float u_0, float v_0){
    float u = u_0;
    float v = v_0;

    int i = 0;
    VECTOR Q = S_nurbs(u, v, s);
    // printf("Q_%d : %f | %f | %f \n",i, Q.x, Q.y, Q.z);
    while (i < 7){ // !crit_1(u, v, s, P) || !crit_2(u, v, s, P)
        // printf("%f | %f \n ", u, v);
        float det = det_sys(u, v, s, P);

        float ui = u;
        float vi = v;

        u = next_ui(ui, vi, det, s, P) + ui;
        v = next_vi(ui, vi, det, s, P) + vi;
        // printf("u_i+1 = %f \n", u);
        // printf("v_i+1 = %f \n", v);

        
        if (u < 0){
            u = 0.0;
        }
        if (u >= 1){
            u = 0.999;
            // u = 1-u;
        }
        
        if (v < 0){
            v = 0.0;
        }
        if (v >= 1){
            v = 0.999;
            // v = fmax(1-v, 0);
        }
        i++;
        VECTOR Q = S_nurbs(u, v, s);
        // printf("Q_%d : %f | %f | %f \n",i, Q.x, Q.y, Q.z);
        if (i == 100){
            return S_nurbs(u, v, s);
        }        
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





