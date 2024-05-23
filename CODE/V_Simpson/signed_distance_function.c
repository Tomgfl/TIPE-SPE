#include "signed_distance_function.h"
#include "utiles.h"
#include <stdio.h>
#include <stdlib.h>



extern float time_scene;


// --- FONCTIONS DE SDF --- //
res_SDF SDF_Objet(vector p, OBJET obj) {
    res_SDF res;
    // if (obj.type == 0) {
    //     res =SDF_sphere(p, obj.param, obj.couleur);
    // }   else if (obj.type == -6) {
    //     res =SDF_sphere(p, obj.param, obj.couleur);
    // }   else if (obj.type == -5) {
    //     res =SDF_sphere(p, obj.param, obj.couleur);
    // }   else if (obj.type == -4) {
    //     res =SDF_sphere(p, obj.param, obj.couleur);
    if (obj.type == -9) {
        param_opsimple* args = (param_opsimple*) obj.param;
        res = SDF_Objet(rotation_z(p, args->k), args->o1);
    }   else if (obj.type == -8) {
        param_opsimple* args = (param_opsimple*) obj.param;
        res = SDF_Objet(rotation_y(v_sub(p,obj.centre), args->k), args->o1);
    }   else if (obj.type == -7) {
        param_opsimple* args = (param_opsimple*) obj.param;
        res = SDF_Objet(rotation_x(v_sub(p,obj.centre), args->k), args->o1);
    }   else if (obj.type == -3) {
        res = SubstractSDF (p, obj.param);
    }   else if (obj.type == -2) {
        res =  IntersectSDF (p, obj.param); 
    }   else if (obj.type == -1) {
        res = UnionSDF(p, obj.param); 
    }   else if (obj.type == 0) {
        res = SDF_sphere(p, obj.param, obj.couleur);
    }   else if (obj.type == 1) {
        res = SDF_Tor(p, obj.param, obj.couleur);
    }   else if (obj.type == 2) {
        res = SDF_cylindre(p, obj.param, obj.couleur);
    }   else if (obj.type == 3) {
        res = SDF_Cone(p, obj.param, obj.couleur);
    }   else if (obj.type == 4) {
        res = SDF_Pyramide(p, obj.param, obj.couleur);
    }   else if (obj.type == 5) {
        res = SDF_box(p, obj.param, obj.couleur);
    }   else if (obj.type == 6) {
        res = SDF_triangle(p, obj.param, obj.couleur);
    }   else {
        res = SDF_Ellipsoid(p, obj.param, obj.couleur);
    }   
    return res;
}


// SDF du plan (n le vecteur normal et m un pts du plan)
res_SDF SDF_plan(vector p, vector n, vector m, color couleur){
    res_SDF res;
    res.c = couleur;

    vector v = v_sub(p,m);

    res.dist = fabs(prod_scal(n,v))/norm_vector(n);
    return res;
}

// Fonction de SDF d'une sphère
res_SDF SDF_sphere(vector p, void* param, color couleur){
    param_sphere* args = (param_sphere*) param;
    vector centre = args->centre;
    float rayon = args->rayon;
    float distance = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y) + (p.z - centre.z)*(p.z - centre.z));
    res_SDF res;
    res.dist = distance - rayon;
    res.c = couleur;
    return res;
}

// Fonction de SDF d'un Tor
res_SDF SDF_Tor(vector p, void* param, color couleur) {
    param_tor* args = (param_tor*) param;
    vector centre = args->centre;
    float R = args->R;
    float r = args->r;
    float distance_xy = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - R;
    float dist = sqrt(distance_xy*distance_xy + (p.z - centre.z)*(p.z - centre.z)) - r;
    res_SDF res = {dist, couleur};
    return res;
}

// SDF d'un cylindre
res_SDF SDF_cylindre(vector p, void* param, color couleur){
    param_cylindre* args = (param_cylindre*) param;
    vector centre = args->centre;
    float H = args->H;
    float r = args->r;
    res_SDF res;
    res.c = couleur;

    float baseCenterZ = centre.z - H / 2.0;
    float distToBase = fabs(p.z - baseCenterZ) - H/2.0;                         // Distance face haute/basse

    float distXY = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - r;   // Distance latérale

    if ((distToBase <= 0) && (distXY <= 0)){           // Intérieur
        res.dist = -fmax(distToBase, distXY);
        return res;    
    } else if ((distToBase <= 0) || (distXY <= 0)){     // Extérieur (dessus/côté)
        res.dist = fmax(distToBase, distXY); 
        return res;
    } else {                                          // Extérieur (diagonale)
        res.dist = sqrt(distToBase * distToBase + distXY * distXY);
        return res;
    }
}

// SDF d'un cône
res_SDF SDF_Cone(vector p, void* param, color couleur){    // Centre du cylindre, rayon r de la base, hauteur H du cylindre
    param_cone* args = (param_cone*) param;
    vector centre = args->centre;
    float H = args->H;
    float r = args->r;
    res_SDF res;
    res.c = couleur;

    float baseCenterZ = centre.z - H / 2.0;
    float distToBase = fabs(p.z - baseCenterZ) - H/2.0;                         // Distance face haute/basse

    float distXY = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - (r/2)*((H/2 - p.z + centre.z)/H);   // Distance latérale

    if ((distToBase <= 0) && (distXY <= 0)){           // Intérieur
        res.dist = -fmax(distToBase, distXY);
        return res;    
    } else if ((distToBase <= 0) || (distXY <= 0)){     // Extérieur (dessus/côté)
        res.dist = fmax(distToBase, distXY);
        return res;
    } else {                                          // Extérieur (diagonale)
        res.dist = sqrt(distToBase * distToBase + distXY * distXY);
        return res;
    }
}

// SDF d'une pyramide (base carrée) selon le centre de sa base // marche pas
res_SDF SDF_Pyramide(vector p, void* param, color couleur){
    param_pyramide* args = (param_pyramide*) param;
    vector centre = args->centre;
    float H = args->H;
    float c = args->c;
    res_SDF res;
    res.c = couleur;

    float distToBase;
    if (p.z > centre.z + H){
        distToBase = p.z - centre.z + H;
    }   else{
        distToBase = centre.z - p.z;
    }

    float distTo1, distTo2, distTo3, distTo4;
    return res;
}

// Fonction de SDF d'une boite (parralépipède rectangle)
res_SDF SDF_box(vector p,void* param, color couleur){
    param_box* args = (param_box*) param;
    vector centre = args->centre;
    float L = args->L;
    float l = args->l;
    float h = args->h;
    res_SDF res;
    res.c = couleur;
   
    float dist;
    float d[3];
    d[0] = fabs(p.x - centre.x) - L/2.0;
    d[1] = fabs(p.y - centre.y) - l/2.0;
    d[2] = fabs(p.z - centre.z) - h/2.0;

    float dist_int = fmax(fmax(d[0],d[1]),d[2]);
    float dist_ext = sqrt(fmax(dist_int, 0.0));

    if (dist_int > 0){
        res.dist = dist_int;
        return res;
    } else {
        res.dist = dist_ext;
        return res;
    }
}

res_SDF SDF_triangle(vector p, void* param, color couleur){
    param_triangle* args = (param_triangle*) param;
    vector a = args->a;
    vector b = args->b;
    vector c = args->c;
    res_SDF res;
    res.c = couleur;
    
    vector ab = v_sub(b,a);
    vector bc = v_sub(c,b);
    vector ca = v_sub(a,c);

    vector ba = v_sub(a,b);
    vector cb = v_sub(b,c);
    vector ac = v_sub(c,a);

    vector pa = v_sub(p,a);
    vector pb = v_sub(p,b);
    vector pc = v_sub(p,c);
    
    // Vecteur normal au plan du triangle
    vector n = prod_vect(ab,bc);

    // distance aux droites du contour du triangle
    float d_1 = norm_vector(prod_vect(pa,ab))/norm_vector(ab);
    float d_2 = norm_vector(prod_vect(pb,bc))/norm_vector(bc);
    float d_3 = norm_vector(prod_vect(pa,ca))/norm_vector(ca);

    // Distance au plan du triangle
    float d_plan = fabs(prod_scal(pb,n))/norm_vector(n);

    // Verification si le point est dans le triangle
    vector n_ab = prod_vect(n,ab);
    vector n_bc = prod_vect(n,bc);
    vector n_ca = prod_vect(n,ca);
    float d_trig;

    if (prod_scal(pa,n_ab) > 0.0 &&
        prod_scal(pb,n_bc) > 0.0 && 
        prod_scal(pc,n_ca) > 0.0){
        d_trig = d_plan;
    } else {
        d_trig = fmin(fmin(d_1,d_2),d_3); 
    }
    
    // return SDF_sphere_circonscrite_triangle(p,a,b,c);

    // correction du triangle
    param_triangle* param2 = malloc(sizeof(param_triangle));
    param2->a = a;
    param2->b = b;
    param2->c = c;
    float dist_sphere = SDF_sphere_circonscrite_triangle(p,param2, couleur).dist;
    res.dist = fmax(d_trig,dist_sphere);
    free(param2);

    return res;
}

res_SDF SDF_sphere_circonscrite_triangle(vector p, void* param, color couleur){
    param_triangle* args = (param_triangle*) param;
    vector a = args->a;
    vector b = args->b;
    vector c = args->c;
    res_SDF res;
    res.c = couleur;
    
    vector ab = v_sub(b,a);
    vector bc = v_sub(c,b);
    vector ac = v_sub(c,a);
    vector n = prod_vect(ab,bc);

    // Calcul de la sphere circonscrite au triangle (pour supprimer les droites, aucunes autres methodes (projections... ) n'a fonctionner)
    // Calcule du centre du cercle
    vector I = v_add(a,v_mult_scal(ab,0.5));  // milieu de ab
    vector J = v_add(a,v_mult_scal(ac,0.5)); // milieur de ac
    
    vector vi = prod_vect(n,ab); // vecteur directeur de la mediatrice de ab
    vector vj = prod_vect(n,ac); // vecteur directeur de la mediatrice de ac

    // // resoud le systeme pour trouver l'intersection des mediatrices
    // float t_1,t_2;
    // float det = - vi.x * vj.y + vj.x * vi.y; // determinant du systeme pour trouver l'intersection
    // if (det == 0){ 
    //     // printf("det = 0\n");
    //     if (vi.x != 0){
    //         t_2 = 1.0;
    //         t_1 = (J.x - I.x + vj.x)/(vi.x);
    //     } else if (vj.x != 0){
    //         t_1 = 1.0;
    //         t_2 = (vi.x - J.x + I.x)/(vj.x);
    //     } else {
    //         t_1 = 1.0;
    //         t_2 = 1.0;
    //     }
    // } else {
    //     t_1 = (-vj.y * (J.x - I.x) + vj.x * (J.y - I.y))/det;
    //     t_2 = (vi.x * (J.y - I.y) - vi.y * (J.x - I.x))/det;
    // }

    res_systeme_2 inter_1 = solve_systeme_2(vi.x, -vj.x, vi.y, -vj.y, J.x - I.x, J.y - I.y);
    res_systeme_2 inter_2 = solve_systeme_2(vi.y, -vj.y, vi.z, -vj.z, J.y - I.y, J.z - I.z);
    res_systeme_2 inter_3 = solve_systeme_2(vi.x, -vj.x, vi.z, -vj.z, J.x - I.x, J.z - I.z);

    // if (inter.det == 0.0 || inter.det == -0.0){
    //     // printf("%f|%f|%f\n", vi.x * -vj.y + vi.y * vj.x, vi.x * -vj.z + vi.z * vj.x, vi.y * -vj.z + vi.z * vj.y);
    //     res_systeme_2 inter = solve_systeme_2(vi.y, -vj.y, vi.z, -vj.z, J.y - I.y, J.z - I.z);
    //     if (inter.det == 0.0 || inter.det == -0.0){
    //         res_systeme_2 inter = solve_systeme_2(vi.x, -vj.x, vi.z, -vj.z, J.x - I.x, J.z - I.z);
    //         // printf("ok\n");
    //     }
    // }
    // // printf("%f\n", inter.det);
    
    res_systeme_2 res_syst;

    if (fabs(inter_1.det) > fabs(inter_2.det)){
        res_syst = inter_1;
    } else {
        res_syst = inter_2;
    }

    if (fabs(res_syst.det) < fabs(inter_3.det)){
        res_syst = inter_3;
    }
    
    
    
    vector C_s_1 = v_add(I,v_mult_scal(vi,res_syst.x));
    // vector C_s_2 = v_add(J,v_mult_scal(vj,t_2));

    // printf("%f,%f,%f | %f,%f,%f \n", C_s_1.x,C_s_1.y,C_s_1.z,C_s_2.x,C_s_2.y,C_s_2.z);

    float r_c = norm_vector(v_sub(a,C_s_1));

    param_sphere* param3 = malloc(sizeof(param_sphere));
    param3->centre = C_s_1;
    param3->rayon = r_c;

    float S_c = SDF_sphere(p, param3, couleur).dist;
    free(param3);
    res.dist = S_c;

    return res;
}









// SDF d'une elliposïde
res_SDF SDF_Ellipsoid(vector p, void* param, color couleur){
    param_ellipsoid* args = (param_ellipsoid*) param;
    vector centre = args->centre;
    float a = args->a;
    float b = args->b;
    float c = args->c;
    res_SDF res;
    res.c = couleur;
    

    float distx = p.x - centre.x;
    float disty = p.y - centre.y;
    float distz = p.z - centre.z;

    res.dist = sqrt((distx*distx) / (a*a) + (disty * disty) / (b*b) + (distz * distz) / (c*c)) - 1.0;
    return res;
}



// --- NUUUUT NUUUUT --- //

// Tête 
// res_SDF SDF_head(vector p, vector centre, float rayon){
    
//     res_SDF Contour = SDF_sphere(p, centre, rayon, c_bleu_berlin);		//Centre (0,0,3), rayon 1

//     vector C_oeG = {centre.x - 0.83*rayon, centre.y - 0.4*rayon, centre.z + 0.4*rayon};	//Centre (-0.83, 0.4, 0.34)
//     res_SDF oeilGa = SDF_sphere(p, C_oeG, 0.16*rayon, c_blanc);
//     res_SDF oeilGauche = UnionSDF(Contour, oeilGa);


//     vector C_oeD = {centre.x - 0.83*rayon, centre.y + 0.4*rayon, centre.z + 0.4*rayon};
//     res_SDF oeilDr = SDF_sphere(p, C_oeD, 0.16*rayon, c_blanc);
//     res_SDF Oeils = UnionSDF(oeilGauche, oeilDr);

//     vector A = {centre.x - 0.98*rayon, centre.y, centre.z+0.2*rayon};	//Point (-0.98, 0, 3.2)
//     vector B = {centre.x - 1.37*rayon, centre.y, centre.z+0.13*rayon};	//Point (-1.37, 0, 3.13)
//     vector C1 = {centre.x - 0.97*rayon, centre.y + 0.24*rayon, centre.z + 0.05*rayon};	//Point (-0.97, 0.24, 3.05)
//     vector C2 = {centre.x - 0.97*rayon, centre.y - 0.24*rayon, centre.z + 0.05*rayon};	//Point (-0.97, -0.24, 3.05)
//     vector D = {centre.x - 1.28*rayon, centre.y, centre.z+0.11*rayon};	//Point (-1.28, 0, 3.11)
//     vector E1 = {centre.x - 0.99*rayon, centre.y + 0.13*rayon, centre.z - 0.05*rayon};	//Point (-0.99, 0.23, 2.95)
//     vector E2 = {centre.x - 0.99*rayon, centre.y - 0.13*rayon, centre.z - 0.05*rayon};	//Point (-0.99, -0.13, 2.95)
    
//     res_SDF bec1 = SDF_triangle(p, A, B, C1, c_orange);
//     res_SDF bec2 = SDF_triangle(p, A, B, C2, c_orange);
//     res_SDF bec3 = SDF_triangle(p, C1, D, E1, c_orange);
//     res_SDF bec4 = SDF_triangle(p, E1, D, E2, c_orange);
//     res_SDF bec5 = SDF_triangle(p, E2, D, C2, c_orange);
    
//     res_SDF Bec1_1 = UnionSDF(Oeils, bec1);
//     res_SDF Bec1_2 = UnionSDF(Bec1_1, bec2);
//     res_SDF Bec1_3 = UnionSDF(Bec1_2, bec3);
//     res_SDF Bec1_4 = UnionSDF(Bec1_3, bec4);
//     res_SDF Bec1_5 = UnionSDF(Bec1_4, bec5);
   
//     vector C_Chap1 = {centre.x, centre.y, centre.z + 1.3*rayon};
//     vector C_Chap2 = {centre.x, centre.y, centre.z + 1.025*rayon};

//     res_SDF Chap1 = SDF_cylindre(p, C_Chap1, 0.6*rayon, 0.2*rayon, c_bistre);
//     res_SDF Chap2 = SDF_cylindre(p, C_Chap2, 0.05*rayon, 0.3*rayon, c_bistre);
    
//     res_SDF Chap1_1 = UnionSDF(Bec1_5, Chap1);
//     res_SDF Chap1_2 = UnionSDF(Chap1_1, Chap2);   
    
//     return Chap1_2;
// }


// // Corps
// res_SDF SDF_corps(vector p, vector centre, float rayon){
//     res_SDF Contour = SDF_sphere(p, centre, rayon, c_bleu_berlin);

//     vector C_Bas = {centre.x, centre.y, centre.z - rayon};
//     res_SDF Bas = SDF_box(p, C_Bas, rayon, rayon, rayon/4, c_bleu_berlin);

//     res_SDF Corps = SubstractSDF(Contour, Bas);

//     Corps.centre = centre ;
//     Corps.rayon = rayon ;
//     return Corps;
// }


// // Total 
// res_SDF SDF_Pingoo(vector p, vector centre, float rayon){
//     vector C_Tete = {centre.x, centre.y, centre.z + rayon/2};
//     res_SDF Tete = SDF_head(p, C_Tete, 1.1*rayon/2);

//     vector C_Corps = {centre.x, centre.y, centre.z - 0.8*rayon/3};
//     res_SDF Corps = SDF_corps(p, C_Corps, 2.1*rayon/3);

//     // res_SDF Pingoo = SmoothUnionSDF(Tete, Corps, 0.05);
//     res_SDF Pingoo = UnionSDF(Tete, Corps);
//     Pingoo.centre = centre ;
//     Pingoo.rayon = rayon ;
//     return Pingoo;
// }




// --- TESTS --- //
// res_SDF mult_objects(vector pos, color couleur){
//     res_SDF res;
//     res.c = couleur;
    
//     // translate
//     // float iTime = 1.0;
    
//     // pos.x += 0.0;
//     // pos.y += 0.0;
//     // pos.z += 0.0;

//     vector modResult;
//     // modResult.x = fmodf(pos.x, 2.0);
//     modResult.y = fmodf(pos.y, 2.0);
//     modResult.x = fmodf(pos.x, 2.0);
//     // modResult.y = pos.y;
//     // modResult.z = fmodf(pos.z, 2.0);
//     modResult.z = pos.z;

//     //float d1 = sqrt((modResult.x - 1.0) * (modResult.x - 1.0) + (modResult.y - 1.0) * (modResult.y - 1.0) + (modResult.z - 1.0) * (modResult.z - 1.0)) - 0.54321;
//     // float d1 = SDF_box(modResult, (vector){1.0,1.0,1.0}, 0.5,0.5,0.5);
//     float d1 = SDF_Tor(modResult, (vector){1.0,1.0,-1}, 0.5, 0.3, couleur).dist;
//     res.dist = d1;
//     return res;
// }

// float fractal_1_test(vector z) {
//     vector a1 = {1.0, 1.0, 1.0};
//     vector a2 = {-1.0, -1.0, 1.0};
//     vector a3 = {1.0, -1.0, -1.0};
//     vector a4 = {-1.0, 1.0, -1.0};
//     vector c;
//     int n = 0;
//     float dist, d;
//     int Iterations = 15;
//     float Scale = 2.0;

//     while (n < Iterations) {
//         c = a1;
//         dist = sqrt(pow(z.x - a1.x, 2) + pow(z.y - a1.y, 2) + pow(z.z - a1.z, 2));
//         d = sqrt(pow(z.x - a2.x, 2) + pow(z.y - a2.y, 2) + pow(z.z - a2.z, 2));
//         if (d < dist) {
//             c = a2;
//             dist = d;
//         }
//         d = sqrt(pow(z.x - a3.x, 2) + pow(z.y - a3.y, 2) + pow(z.z - a3.z, 2));
//         if (d < dist) {
//             c = a3;
//             dist = d;
//         }
//         d = sqrt(pow(z.x - a4.x, 2) + pow(z.y - a4.y, 2) + pow(z.z - a4.z, 2));
//         if (d < dist) {
//             c = a4;
//             dist = d;
//         }

//         z.x = Scale * z.x - c.x * (Scale - 1.0);
//         z.y = Scale * z.y - c.y * (Scale - 1.0);
//         z.z = Scale * z.z - c.z * (Scale - 1.0);
//         n++;
//     }

//     return sqrt(pow(z.x, 2) + pow(z.y, 2) + pow(z.z, 2)) * pow(Scale, -n);
// }





// // --- ROTATIONS --- //
// renvoie le produit entre la matrice de rotation Rx et le vec v
vector rotation_x (vector v, float angle){      // angle en degres
    return (vector){v.x, v.y*cos(angle*3.14/180) - v.z*sin(angle*3.14/180), v.y*sin(angle*3.14/180) + v.z*cos(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Ry et le vec v
vector rotation_y (vector v, float angle){      // angle en degres
    return (vector){v.x*cos(angle*3.14/180) + v.z*sin(angle*3.14/180), v.y, v.z*cos(angle*3.14/180) - v.x*sin(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rz et le vec v
vector rotation_z (vector v, float angle){      // angle en degres
    return (vector){v.x*cos(angle*3.14/180) - v.y*sin(angle*3.14/180), v.x*sin(angle*3.14/180) + v.y*cos(angle*3.14/180), v.z};
}




// // --- OPERATIONS --- //
// Union de 2 formes
res_SDF UnionSDF (vector p, void* param){
    param_opdouble* args = (param_opdouble*) param;
    res_SDF r1 = SDF_Objet(p, args->o1);
    res_SDF r2 = SDF_Objet(p, args->o2);
    return min_sdf(r1,r2);
}

// Intersection de 2 formes
res_SDF IntersectSDF (vector p, void* param){
    param_opdouble* args = (param_opdouble*) param;
    res_SDF r1 = SDF_Objet(p, args->o1);
    res_SDF r2 = SDF_Objet(p, args->o2);
    return max_sdf(r1,r2);
}

// Soustraction : On enlève le forme 2 de la forme 1
res_SDF SubstractSDF (vector p, void* param){
    param_opdouble* args = (param_opdouble*) param;
    res_SDF r1 = SDF_Objet(p, args->o1);
    res_SDF r2 = SDF_Objet(p, args->o2);
    return max_sdf(r1,(res_SDF){-r2.dist, r2.c});
}

// // -- SMOOTH -- //
// // Union Smooth
// // float SmoothUnionSDF(float d1, float d2, float k){
// //     float h = max(k-abs(d1-d2),0.0);
// //     return (min(d1, d2) - h*h*0.25/k);
// // }


// // res_SDF SmoothUnionSDF(res_SDF d1, res_SDF d2, float k){
// //     float h = d1-d2;
// //     return 0.5*((d1+d2) - sqrt(h*h+k));
// // }

// // // Intersection Smooth 
// // res_SDF SmoothIntersectSDF(res_SDF d1, res_SDF d2, float k){
// //     return -SmoothUnionSDF(-d1,-d2,k);
// // }

// // // Soustraction Smooth
// // res_SDF SmoothSubstractSDF(res_SDF d1, res_SDF d2, float k){
// //     return -SmoothUnionSDF(-d1,d2,k);
// // }


// res_SDF Disturb(vector p, res_SDF d) {
//     float displacement = sin((sin(time_scene)*sin(time_scene)*3 + 2) * p.x) * sin((sin(time_scene)*sin(time_scene)*3 + 2) * p.y) * sin((sin(time_scene)*sin(time_scene)*3 + 2) * p.z) * 0.25;
//     // float sphere_0 = distance_from_sphere(p, vec3(0.0), 1.0);
//     res_SDF res;
//     res.c = d.c;
//     res.centre = d.centre;
//     res.rayon = d.rayon;
//     res.dist = displacement + d.dist;

//     return res;
// }




