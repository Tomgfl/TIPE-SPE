#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"
#include "options.h"

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define SIGN(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)
#define CLAMP(d, min, max) (((d) < (min)) ? (min) : (((d) > (max)) ? (max) : (d)))

double clamp(double d, double min, double max) {
  const double t = d < min ? min : d;
  return t > max ? max : t;
}

// --- FONCTIONS DE SDF --- //

// Fonction de SDF d'une sphère
float SDF_sphere(vector p, vector centre, float rayon){
    float distance = sqrt( (p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y) + (p.z - centre.z)*(p.z - centre.z) );
    return distance - rayon;
}


// Fonction de SDF d'un Tor
float SDF_Tor(vector p, vector centre, float R, float r) {
    float distance_xy = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - R;
    return sqrt(distance_xy*distance_xy + (p.z - centre.z)*(p.z - centre.z)) - r;
}


// SDF d'un cylindre
float SDF_cylindre(vector p, vector centre, float H, float r){
    
    float baseCenterZ = centre.z - H / 2.0;
    float distToBase = fabs(p.z - baseCenterZ) - H/2.0;                         // Distance face haute/basse

    float distXY = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - r;   // Distance latérale

    if ((distToBase <= 0) && (distXY <= 0)) {           // Intérieur
        return -MAX(distToBase, distXY);    
    } else if ((distToBase <= 0) || (distXY <= 0)){     // Extérieur (dessus/côté)
        return MAX(distToBase, distXY);
    }   else {                                          // Extérieur (diagonale)
        return sqrt(distToBase * distToBase + distXY * distXY);
    }
}


// SDF d'un cône
float SDF_Cone(vector p, vector centre, float H, float r){    // Centre du cylindre, rayon r de la base, hauteur H du cylindre
    
    float baseCenterZ = centre.z - H / 2.0;
    float distToBase = fabs(p.z - baseCenterZ) - H/2.0;                         // Distance face haute/basse

    float distXY = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - (r/2)*((H/2 - p.z + centre.z)/H);   // Distance latérale

    if ((distToBase <= 0) && (distXY <= 0)) {           // Intérieur
        return -MAX(distToBase, distXY);    
    } else if ((distToBase <= 0) || (distXY <= 0)){     // Extérieur (dessus/côté)
        return MAX(distToBase, distXY);
    }   else {                                          // Extérieur (diagonale)
        return sqrt(distToBase * distToBase + distXY * distXY);
    }
}



// SDF d'une pyramide (base carrée) selon le centre de sa base
float SDF_Pyramide(vector p, vector centre, float H, float c){

    float distToBase;
    if (p.z > centre.z + H){
        distToBase = p.z - centre.z + H;
    }   else{
        distToBase = centre.z - p.z;
    }

    float distTo1, distTo2, distTo3, distTo4;

    return 0;
}


// Fonction de SDF d'une boite (parralépipède rectangle)
float SDF_box(vector p, vector centre, float L, float l, float h){
    float dist;
    float d[3];
    d[0] = fabs(p.x - centre.x) - L/2.0;
    d[1] = fabs(p.y - centre.y) - l/2.0;
    d[2] = fabs(p.z - centre.z) - h/2.0;

    float dist_int = fmax(fmax(d[0],d[1]),d[2]);
    float dist_ext = sqrt(fmax(dist_int, 0.0));

    if (dist_int > 0){
        return dist_int;
    }   else{
        return dist_ext;
    }
}



float SDF_triangle(vector p, vector a, vector b, vector c){
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
        d_trig = MIN(MIN(d_1,d_2),d_3); 
    }
    
    // return SDF_sphere_circonscrite_triangle(p,a,b,c);

    return MAX(d_trig,SDF_sphere_circonscrite_triangle(p,a,b,c));
}


float SDF_sphere_circonscrite_triangle(vector p, vector a, vector b, vector c){
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

    // resoud le systeme pour trouver l'intersection des mediatrices
    float t_1,t_2;
    float det = - vi.x * vj.y + vj.x * vi.y; // determinant du systeme pour trouver l'intersection
    if (det == 0){ 
        // printf("det = 0\n");
        if (vi.x != 0){
            t_2 = 1.0;
            t_1 = (J.x - I.x + vj.x)/(vi.x);
        } else if (vj.x != 0){
            t_1 = 1.0;
            t_2 = (vi.x - J.x + I.x)/(vj.x);
        } else {
            t_1 = 1.0;
            t_2 = 1.0;
        }
    } else {
        t_1 = (-vj.y * (J.x - I.x) + vj.x * (J.y - I.y))/det;
        t_2 = (vi.x * (J.y - I.y) - vi.y * (J.x - I.x))/det;
    }
    
    vector C_s_1 = v_add(I,v_mult_scal(vi,t_1));
    vector C_s_2 = v_add(J,v_mult_scal(vj,t_2));

    // printf("%f,%f,%f | %f,%f,%f \n", C_s_1.x,C_s_1.y,C_s_1.z,C_s_2.x,C_s_2.y,C_s_2.z);

    float r_c = norm_vector(v_sub(a,C_s_1));

    float S_c = SDF_sphere(p,C_s_1,r_c);

    return S_c;
}








// SDF du plan (n le vecteur normal et m un pts du plan)
float SDF_plan(vector p, vector n, vector m){
    vector v = v_sub(p,m);
    return (fabs(prod_scal(n,v))/norm_vector(n));
}


// SDF d'une elliposïde
float SDF_Ellipsoid(vector p, vector centre, float a, float b, float c){
    float distx = p.x - centre.x;
    float disty = p.y - centre.y;
    float distz = p.z - centre.z;
    return sqrt((distx*distx) / (a*a) + (disty * disty) / (b*b) + (distz * distz) / (c*c)) - 1.0;
}



// --- NUUUUT NUUUUT --- //

// Tête 
float SDF_head(vector p, vector centre, float rayon){
    float Contour = SDF_sphere(p, centre, rayon);		//Centre (0,0,3), rayon 1

    vector C_oeG = {centre.x - 0.83*rayon, centre.y - 0.4*rayon, centre.z + 0.4*rayon};	//Centre (-0.83, 0.4, 0.34)
    float oeilGa = SDF_sphere(p, C_oeG, 0.16*rayon);
    float oeilGauche = UnionSDF(Contour, oeilGa);


    vector C_oeD = {centre.x - 0.83*rayon, centre.y + 0.4*rayon, centre.z + 0.4*rayon};
    float oeilDr = SDF_sphere(p, C_oeD, 0.16*rayon);
    float Oeils = UnionSDF(oeilGauche, oeilDr);

    vector A = {centre.x - 0.98*rayon, centre.y, centre.z+0.2*rayon};	//Point (-0.98, 0, 3.2)
    vector B = {centre.x - 1.37*rayon, centre.y, centre.z+0.13*rayon};	//Point (-1.37, 0, 3.13)
    vector C1 = {centre.x - 0.97*rayon, centre.y + 0.24*rayon, centre.z + 0.05*rayon};	//Point (-0.97, 0.24, 3.05)
    vector C2 = {centre.x - 0.97*rayon, centre.y - 0.24*rayon, centre.z + 0.05*rayon};	//Point (-0.97, -0.24, 3.05)
    vector D = {centre.x - 1.28*rayon, centre.y, centre.z+0.11*rayon};	//Point (-1.28, 0, 3.11)
    vector E1 = {centre.x - 0.99*rayon, centre.y + 0.13*rayon, centre.z - 0.05*rayon};	//Point (-0.99, 0.23, 2.95)
    vector E2 = {centre.x - 0.99*rayon, centre.y - 0.13*rayon, centre.z - 0.05*rayon};	//Point (-0.99, -0.13, 2.95)
    
    float bec1 = SDF_triangle(p, A, B, C1);
    float bec2 = SDF_triangle(p, A, B, C2);
    float bec3 = SDF_triangle(p, C1, D, E1);
    float bec4 = SDF_triangle(p, E1, D, E2);
    float bec5 = SDF_triangle(p, E2, D, C2);
    
    float Bec1_1 = UnionSDF(Oeils, bec1);
    float Bec1_2 = UnionSDF(Bec1_1, bec2);
    float Bec1_3 = UnionSDF(Bec1_2, bec3);
    float Bec1_4 = UnionSDF(Bec1_3, bec4);
    float Bec1_5 = UnionSDF(Bec1_4, bec5);
   
    vector C_Chap1 = {centre.x, centre.y, centre.z + 1.3*rayon};
    vector C_Chap2 = {centre.x, centre.y, centre.z + 1.025*rayon};
    float Chap1 = SDF_cylindre(p, C_Chap1, 0.6*rayon, 0.2*rayon);
    float Chap2 = SDF_cylindre(p, C_Chap2, 0.05*rayon, 0.3*rayon);
    
    float Chap1_1 = UnionSDF(Bec1_5, Chap1);
    float Chap1_2 = UnionSDF(Chap1_1, Chap2);   
    
    return Chap1_2;
}


// Corps
float SDF_corps(vector p, vector centre, float rayon){
    float Contour = SDF_sphere(p, centre, rayon);

    vector C_Bas = {centre.x, centre.y, centre.z - rayon};
    float Bas = SDF_box(p, C_Bas, rayon, rayon, rayon/4);

    float Corps = SubstractSDF(Contour, Bas);

    return Corps;
}


// Total 
float SDF_Pingoo(vector p, vector centre, float rayon){
    vector C_Tete = {centre.x, centre.y, centre.z + rayon/2};
    float Tete = SDF_head(p, C_Tete, 1.1*rayon/2);

    vector C_Corps = {centre.x, centre.y, centre.z - 0.8*rayon/3};
    float Corps = SDF_corps(p, C_Corps, 2.1*rayon/3);

    float Pingoo = SmoothUnionSDF(Tete, Corps, 0.05);
    return Pingoo;
}




// --- TESTS --- //
float mult_objects(vector pos) {
    // translate
    // float iTime = 1.0;
    
    // pos.x += 0.0;
    // pos.y += 0.0;
    // pos.z += 0.0;

    vector modResult;
    // modResult.x = fmodf(pos.x, 2.0);
    modResult.y = fmodf(pos.y, 2.0);
    modResult.x = fmodf(pos.x, 2.0);
    // modResult.y = pos.y;
    // modResult.z = fmodf(pos.z, 2.0);
    modResult.z = pos.z;

    //float d1 = sqrt((modResult.x - 1.0) * (modResult.x - 1.0) + (modResult.y - 1.0) * (modResult.y - 1.0) + (modResult.z - 1.0) * (modResult.z - 1.0)) - 0.54321;
    // float d1 = SDF_box(modResult, (vector){1.0,1.0,1.0}, 0.5,0.5,0.5);
    float d1 = SDF_Tor(modResult, (vector){1.0,1.0,-1}, 0.5, 0.3);
    return d1;
}

float fractal_1_test(vector z) {
    vector a1 = {1.0, 1.0, 1.0};
    vector a2 = {-1.0, -1.0, 1.0};
    vector a3 = {1.0, -1.0, -1.0};
    vector a4 = {-1.0, 1.0, -1.0};
    vector c;
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
vector rotation_x (vector v, float angle){// angle en degres
    return (vector){v.x, v.y*cos(angle*3.14/180) - v.z*sin(angle*3.14/180), v.y*sin(angle*3.14/180) + v.z*cos(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
vector rotation_y (vector v, float angle){// angle en degres
    return (vector){v.x*cos(angle*3.14/180) + v.z*sin(angle*3.14/180), v.y, v.z*cos(angle*3.14/180) - v.x*sin(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
vector rotation_z (vector v, float angle){// angle en degres
    return (vector){v.x*cos(angle*3.14/180) - v.y*sin(angle*3.14/180), v.x*sin(angle*3.14/180) + v.y*cos(angle*3.14/180), v.z};
}




// --- OPERATIONS --- //
// Union de 2 formes
float UnionSDF (float d1, float d2){
    return MIN(d1,d2);
}

// Intersection de 2 formes
float IntersectSDF (float d1, float d2){
    return MAX(d1,d2);
}

// Soustraction : On enlève le forme 2 de la forme 1
float SubstractSDF (float d1, float d2){
    return MAX(d1, -d2); 
}

// -- SMOOTH -- //
// Union Smooth
// float SmoothUnionSDF(float d1, float d2, float k){
//     float h = max(k-abs(d1-d2),0.0);
//     return (min(d1, d2) - h*h*0.25/k);
// }
float SmoothUnionSDF(float d1, float d2, float k){
    float h = d1-d2;
    return 0.5*( (d1+d2) - sqrt(h*h+k));
}

// Intersection Smooth 
float SmoothIntersectSDF(float d1, float d2, float k){
    return -SmoothUnionSDF(-d1,-d2,k);
}

// Soustraction Smooth
float SmoothSubstractSDF(float d1, float d2, float k){
    return -SmoothUnionSDF(-d1,d2,k);
}




