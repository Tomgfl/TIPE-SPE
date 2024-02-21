#include "signed_distance_function.h"
#include <stdio.h>


extern float time_scene;


// --- FONCTIONS DE SDF --- //

// Fonction de SDF d'une sphère
RES_SDF SDF_sphere(VECTOR p, VECTOR centre, float rayon, COLOR couleur){
    float distance = sqrt( (p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y) + (p.z - centre.z)*(p.z - centre.z) );
    RES_SDF res;
    res.dist = distance - rayon;
    res.c = couleur;
    return res;
}


// Fonction de SDF d'un Tor
RES_SDF SDF_Tor(VECTOR p, VECTOR centre, float R, float r, COLOR couleur) {
    float distance_xy = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - R;
    float dist = sqrt(distance_xy*distance_xy + (p.z - centre.z)*(p.z - centre.z)) - r;
    RES_SDF res = {dist, couleur};
    return res;
}


// SDF d'un cylindre
RES_SDF SDF_cylindre(VECTOR p, VECTOR centre, float H, float r, COLOR couleur){
    RES_SDF res;
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
RES_SDF SDF_Cone(VECTOR p, VECTOR centre, float H, float r, COLOR couleur){    // Centre du cylindre, rayon r de la base, hauteur H du cylindre
    RES_SDF res;
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
RES_SDF SDF_Pyramide(VECTOR p, VECTOR centre, float H, float c, COLOR couleur){
    RES_SDF res;
    res.c = couleur;

    float distToBase;
    if (p.z > centre.z + H){
        distToBase = p.z - centre.z + H;
    }   else{
        distToBase = centre.z - p.z;
    }

    float distTo1, distTo2, distTo3, distTo4;

    // res.dist = ??

    return res;
}


// Fonction de SDF d'une boite (parralépipède rectangle)
RES_SDF SDF_box(VECTOR p, VECTOR centre, float L, float l, float h, COLOR couleur){
    RES_SDF res;
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



RES_SDF SDF_triangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c, COLOR couleur){
    RES_SDF res;
    res.c = couleur;

    VECTOR ab = v_sub(b,a);
    VECTOR bc = v_sub(c,b);
    VECTOR ca = v_sub(a,c);

    VECTOR ba = v_sub(a,b);
    VECTOR cb = v_sub(b,c);
    VECTOR ac = v_sub(c,a);

    VECTOR pa = v_sub(p,a);
    VECTOR pb = v_sub(p,b);
    VECTOR pc = v_sub(p,c);
    
    // Vecteur normal au plan du triangle
    VECTOR n = prod_vect(ab,bc);

    // distance aux droites du contour du triangle
    float d_1 = norm_vector(prod_vect(pa,ab))/norm_vector(ab);
    float d_2 = norm_vector(prod_vect(pb,bc))/norm_vector(bc);
    float d_3 = norm_vector(prod_vect(pa,ca))/norm_vector(ca);

    // Distance au plan du triangle
    float d_plan = fabs(prod_scal(pb,n))/norm_vector(n);

    // Verification si le point est dans le triangle
    VECTOR n_ab = prod_vect(n,ab);
    VECTOR n_bc = prod_vect(n,bc);
    VECTOR n_ca = prod_vect(n,ca);
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
    float dist_sphere = SDF_sphere_circonscrite_triangle(p,a,b,c, couleur).dist;
    res.dist = fmax(d_trig,dist_sphere);

    return res;
}


RES_SDF SDF_sphere_circonscrite_triangle(VECTOR p, VECTOR a, VECTOR b, VECTOR c, COLOR couleur){
    RES_SDF res;
    res.c = couleur;

    VECTOR ab = v_sub(b,a);
    VECTOR bc = v_sub(c,b);
    VECTOR ac = v_sub(c,a);
    VECTOR n = prod_vect(ab,bc);

    // Calcul de la sphere circonscrite au triangle (pour supprimer les droites, aucunes autres methodes (projections... ) n'a fonctionner)
    // Calcule du centre du cercle
    VECTOR I = v_add(a,v_mult_scal(ab,0.5));  // milieu de ab
    VECTOR J = v_add(a,v_mult_scal(ac,0.5)); // milieur de ac
    
    VECTOR vi = prod_vect(n,ab); // vecteur directeur de la mediatrice de ab
    VECTOR vj = prod_vect(n,ac); // vecteur directeur de la mediatrice de ac

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

    RES_SYS_2 inter_1 = solve_systeme_2(vi.x, -vj.x, vi.y, -vj.y, J.x - I.x, J.y - I.y);
    RES_SYS_2 inter_2 = solve_systeme_2(vi.y, -vj.y, vi.z, -vj.z, J.y - I.y, J.z - I.z);
    RES_SYS_2 inter_3 = solve_systeme_2(vi.x, -vj.x, vi.z, -vj.z, J.x - I.x, J.z - I.z);

    // if (inter.det == 0.0 || inter.det == -0.0){
    //     // printf("%f|%f|%f\n", vi.x * -vj.y + vi.y * vj.x, vi.x * -vj.z + vi.z * vj.x, vi.y * -vj.z + vi.z * vj.y);
    //     RES_SYS_2 inter = solve_systeme_2(vi.y, -vj.y, vi.z, -vj.z, J.y - I.y, J.z - I.z);
    //     if (inter.det == 0.0 || inter.det == -0.0){
    //         RES_SYS_2 inter = solve_systeme_2(vi.x, -vj.x, vi.z, -vj.z, J.x - I.x, J.z - I.z);
    //         // printf("ok\n");
    //     }
    // }
    // // printf("%f\n", inter.det);
    
    RES_SYS_2 res_syst;

    if (fabs(inter_1.det) > fabs(inter_2.det)){
        res_syst = inter_1;
    } else {
        res_syst = inter_2;
    }

    if (fabs(res_syst.det) < fabs(inter_3.det)){
        res_syst = inter_3;
    }
    
    
    
    VECTOR C_s_1 = v_add(I,v_mult_scal(vi,res_syst.x));
    // vector C_s_2 = v_add(J,v_mult_scal(vj,t_2));

    // printf("%f,%f,%f | %f,%f,%f \n", C_s_1.x,C_s_1.y,C_s_1.z,C_s_2.x,C_s_2.y,C_s_2.z);

    float r_c = norm_vector(v_sub(a,C_s_1));

    float S_c = SDF_sphere(p,C_s_1,r_c, couleur).dist;

    res.dist = S_c;

    return res;
}








// SDF du plan (n le vecteur normal et m un pts du plan)
RES_SDF SDF_plan(VECTOR p, VECTOR n, VECTOR m, COLOR couleur){
    RES_SDF res;
    res.c = couleur;

    VECTOR v = v_sub(p,m);

    res.dist = fabs(prod_scal(n,v))/norm_vector(n);
    return res;
}


// SDF d'une elliposïde
RES_SDF SDF_Ellipsoid(VECTOR p, VECTOR centre, float a, float b, float c, COLOR couleur){
    RES_SDF res;
    res.c = couleur;

    float distx = p.x - centre.x;
    float disty = p.y - centre.y;
    float distz = p.z - centre.z;

    res.dist = sqrt((distx*distx) / (a*a) + (disty * disty) / (b*b) + (distz * distz) / (c*c)) - 1.0;
    return res;
}



// --- NUUUUT NUUUUT --- //

// Tête 
RES_SDF SDF_head(VECTOR p, VECTOR centre, float rayon){
    
    RES_SDF Contour = SDF_sphere(p, centre, rayon, c_bleu_berlin);		//Centre (0,0,3), rayon 1

    VECTOR C_oeG = {centre.x - 0.83*rayon, centre.y - 0.4*rayon, centre.z + 0.4*rayon};	//Centre (-0.83, 0.4, 0.34)
    RES_SDF oeilGa = SDF_sphere(p, C_oeG, 0.16*rayon, c_blanc);
    RES_SDF oeilGauche = UnionSDF(Contour, oeilGa);


    VECTOR C_oeD = {centre.x - 0.83*rayon, centre.y + 0.4*rayon, centre.z + 0.4*rayon};
    RES_SDF oeilDr = SDF_sphere(p, C_oeD, 0.16*rayon, c_blanc);
    RES_SDF Oeils = UnionSDF(oeilGauche, oeilDr);

    VECTOR A = {centre.x - 0.98*rayon, centre.y, centre.z+0.2*rayon};	//Point (-0.98, 0, 3.2)
    VECTOR B = {centre.x - 1.37*rayon, centre.y, centre.z+0.13*rayon};	//Point (-1.37, 0, 3.13)
    VECTOR C1 = {centre.x - 0.97*rayon, centre.y + 0.24*rayon, centre.z + 0.05*rayon};	//Point (-0.97, 0.24, 3.05)
    VECTOR C2 = {centre.x - 0.97*rayon, centre.y - 0.24*rayon, centre.z + 0.05*rayon};	//Point (-0.97, -0.24, 3.05)
    VECTOR D = {centre.x - 1.28*rayon, centre.y, centre.z+0.11*rayon};	//Point (-1.28, 0, 3.11)
    VECTOR E1 = {centre.x - 0.99*rayon, centre.y + 0.13*rayon, centre.z - 0.05*rayon};	//Point (-0.99, 0.23, 2.95)
    VECTOR E2 = {centre.x - 0.99*rayon, centre.y - 0.13*rayon, centre.z - 0.05*rayon};	//Point (-0.99, -0.13, 2.95)
    
    RES_SDF bec1 = SDF_triangle(p, A, B, C1, c_orange);
    RES_SDF bec2 = SDF_triangle(p, A, B, C2, c_orange);
    RES_SDF bec3 = SDF_triangle(p, C1, D, E1, c_orange);
    RES_SDF bec4 = SDF_triangle(p, E1, D, E2, c_orange);
    RES_SDF bec5 = SDF_triangle(p, E2, D, C2, c_orange);
    
    RES_SDF Bec1_1 = UnionSDF(Oeils, bec1);
    RES_SDF Bec1_2 = UnionSDF(Bec1_1, bec2);
    RES_SDF Bec1_3 = UnionSDF(Bec1_2, bec3);
    RES_SDF Bec1_4 = UnionSDF(Bec1_3, bec4);
    RES_SDF Bec1_5 = UnionSDF(Bec1_4, bec5);
   
    VECTOR C_Chap1 = {centre.x, centre.y, centre.z + 1.3*rayon};
    VECTOR C_Chap2 = {centre.x, centre.y, centre.z + 1.025*rayon};

    RES_SDF Chap1 = SDF_cylindre(p, C_Chap1, 0.6*rayon, 0.2*rayon, c_bistre);
    RES_SDF Chap2 = SDF_cylindre(p, C_Chap2, 0.05*rayon, 0.3*rayon, c_bistre);
    
    RES_SDF Chap1_1 = UnionSDF(Bec1_5, Chap1);
    RES_SDF Chap1_2 = UnionSDF(Chap1_1, Chap2);   
    
    return Chap1_2;
}


// Corps
RES_SDF SDF_corps(VECTOR p, VECTOR centre, float rayon){
    RES_SDF Contour = SDF_sphere(p, centre, rayon, c_bleu_berlin);

    VECTOR C_Bas = {centre.x, centre.y, centre.z - rayon};
    RES_SDF Bas = SDF_box(p, C_Bas, rayon, rayon, rayon/4, c_bleu_berlin);

    RES_SDF Corps = SubstractSDF(Contour, Bas);

    return Corps;
}


// Total 
RES_SDF SDF_Pingoo(VECTOR p, VECTOR centre, float rayon){
    VECTOR C_Tete = {centre.x, centre.y, centre.z + rayon/2};
    RES_SDF Tete = SDF_head(p, C_Tete, 1.1*rayon/2);

    VECTOR C_Corps = {centre.x, centre.y, centre.z - 0.8*rayon/3};
    RES_SDF Corps = SDF_corps(p, C_Corps, 2.1*rayon/3);

    // RES_SDF Pingoo = SmoothUnionSDF(Tete, Corps, 0.05);
    RES_SDF Pingoo = UnionSDF(Tete, Corps);
    return Pingoo;
}




// --- TESTS --- //
RES_SDF mult_objects(VECTOR pos, COLOR couleur){
    RES_SDF res;
    res.c = couleur;
    
    // translate
    // float iTime = 1.0;
    
    // pos.x += 0.0;
    // pos.y += 0.0;
    // pos.z += 0.0;

    VECTOR modResult;
    // modResult.x = fmodf(pos.x, 2.0);
    modResult.y = fmodf(pos.y, 2.0);
    modResult.x = fmodf(pos.x, 2.0);
    // modResult.y = pos.y;
    // modResult.z = fmodf(pos.z, 2.0);
    modResult.z = pos.z;

    //float d1 = sqrt((modResult.x - 1.0) * (modResult.x - 1.0) + (modResult.y - 1.0) * (modResult.y - 1.0) + (modResult.z - 1.0) * (modResult.z - 1.0)) - 0.54321;
    // float d1 = SDF_box(modResult, (vector){1.0,1.0,1.0}, 0.5,0.5,0.5);
    float d1 = SDF_Tor(modResult, (VECTOR){1.0,1.0,-1}, 0.5, 0.3, couleur).dist;
    res.dist = d1;
    return res;
}

float fractal_1_test(VECTOR z) {
    VECTOR a1 = {1.0, 1.0, 1.0};
    VECTOR a2 = {-1.0, -1.0, 1.0};
    VECTOR a3 = {1.0, -1.0, -1.0};
    VECTOR a4 = {-1.0, 1.0, -1.0};
    VECTOR c;
    int n = 0;
    float dist, d;
    int Iterations = 15;
    float Scale = 2.0;

    while (n < Iterations) {
        c = a1;
        dist = sqrt(pow(z.x - a1.x, 2) + pow(z.y - a1.y, 2) + pow(z.z - a1.z, 2));
        d = sqrt(pow(z.x - a2.x, 2) + pow(z.y - a2.y, 2) + pow(z.z - a2.z, 2));
        if (d < dist) {
            c = a2;
            dist = d;
        }
        d = sqrt(pow(z.x - a3.x, 2) + pow(z.y - a3.y, 2) + pow(z.z - a3.z, 2));
        if (d < dist) {
            c = a3;
            dist = d;
        }
        d = sqrt(pow(z.x - a4.x, 2) + pow(z.y - a4.y, 2) + pow(z.z - a4.z, 2));
        if (d < dist) {
            c = a4;
            dist = d;
        }

        z.x = Scale * z.x - c.x * (Scale - 1.0);
        z.y = Scale * z.y - c.y * (Scale - 1.0);
        z.z = Scale * z.z - c.z * (Scale - 1.0);
        n++;
    }

    return sqrt(pow(z.x, 2) + pow(z.y, 2) + pow(z.z, 2)) * pow(Scale, -n);
}





// --- ROTATIONS --- //
// renvoie le produit entre la matrice de rotation Rx et le vec v
VECTOR rotation_x (VECTOR v, float angle){// angle en degres
    return (VECTOR){v.x, v.y*cos(angle*3.14/180) - v.z*sin(angle*3.14/180), v.y*sin(angle*3.14/180) + v.z*cos(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
VECTOR rotation_y (VECTOR v, float angle){// angle en degres
    return (VECTOR){v.x*cos(angle*3.14/180) + v.z*sin(angle*3.14/180), v.y, v.z*cos(angle*3.14/180) - v.x*sin(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
VECTOR rotation_z (VECTOR v, float angle){// angle en degres
    return (VECTOR){v.x*cos(angle*3.14/180) - v.y*sin(angle*3.14/180), v.x*sin(angle*3.14/180) + v.y*cos(angle*3.14/180), v.z};
}




// --- OPERATIONS --- //
// Union de 2 formes
RES_SDF UnionSDF (RES_SDF d1, RES_SDF d2){
    return min_sdf(d1,d2);
    // return fmin(d1, d2);
}

// Intersection de 2 formes
RES_SDF IntersectSDF (RES_SDF d1, RES_SDF d2){
    return max_sdf(d1,d2);
    // return fmax(d1, d2);
}

// Soustraction : On enlève le forme 2 de la forme 1
RES_SDF SubstractSDF (RES_SDF d1, RES_SDF d2){
    return max_sdf(d1,(RES_SDF){-d2.dist, d2.c});
    // return fmax(d1, -d2); 
}

// -- SMOOTH -- //
// Union Smooth
// float SmoothUnionSDF(float d1, float d2, float k){
//     float h = max(k-abs(d1-d2),0.0);
//     return (min(d1, d2) - h*h*0.25/k);
// }


// RES_SDF SmoothUnionSDF(RES_SDF d1, RES_SDF d2, float k){
//     float h = d1-d2;
//     return 0.5*((d1+d2) - sqrt(h*h+k));
// }

// // Intersection Smooth 
// RES_SDF SmoothIntersectSDF(RES_SDF d1, RES_SDF d2, float k){
//     return -SmoothUnionSDF(-d1,-d2,k);
// }

// // Soustraction Smooth
// RES_SDF SmoothSubstractSDF(RES_SDF d1, RES_SDF d2, float k){
//     return -SmoothUnionSDF(-d1,d2,k);
// }


RES_SDF Disturb(VECTOR p, RES_SDF d) {
    float displacement = sin((sin(time_scene)*sin(time_scene)*3 + 2) * p.x) * sin((sin(time_scene)*sin(time_scene)*3 + 2) * p.y) * sin((sin(time_scene)*sin(time_scene)*3 + 2) * p.z) * 0.25;
    // float sphere_0 = distance_from_sphere(p, vec3(0.0), 1.0);
    RES_SDF res;
    res.c = d.c;
    res.dist = displacement + d.dist;

    return res;
}




