#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"

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
float SDF_sphere(coord p, coord centre, float rayon){
    float distance = sqrt( (p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y) + (p.z - centre.z)*(p.z - centre.z) );
    return distance - rayon;
}


// Fonction de SDF d'un Tor
float SDF_Tor(coord p, coord centre, float R, float r) {
    float distance_xy = sqrt((p.x - centre.x)*(p.x - centre.x) + (p.y - centre.y)*(p.y - centre.y)) - R;
    return sqrt(distance_xy*distance_xy + (p.z - centre.z)*(p.z - centre.z)) - r;
}


// SDF d'un cylindre
float SDF_cylindre(coord p, coord centre, float H, float r){
    
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
float SDF_Cone(coord p, coord centre, float H, float r){    // Centre du cylindre, rayon r de la base, hauteur H du cylindre
    
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
float SDF_Pyramide(coord p, coord centre, float H, float c){

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
float SDF_box(coord p, coord centre, float L, float l, float h){
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


// SDF face triangle
float SDF_triangle(coord p, coord a, coord b, coord c){
    vector ba = (vector){b.x-a.x, b.y-a.y, b.z-a.z};
    vector cb = (vector){c.x-b.x, c.y-b.y, c.z-b.z};
    vector ac = (vector){a.x-c.x, a.y-c.y, a.z-c.z};

    vector pa = (vector){p.x-a.x, p.y-a.y, p.z-a.z};
    vector pb = (vector){p.x-b.x, p.y-b.y, p.z-b.z};
    vector pc = (vector){p.x-c.x, p.y-c.y, p.z-c.z};

    vector nor = prod_vect(ba,ac);

    if (SIGN(prod_scal(prod_vect(ba,nor),pa)) + 
        SIGN(prod_scal(prod_vect(cb,nor),pb)) + 
        SIGN(prod_scal(prod_vect(ac,nor),pc)) < .0){
            vector v_1 = v_sub(v_mult_scal(ba,clamp(prod_scal(ba,pa)/prod_scal(ba,ba),0.0,1.0)),pa);
            vector v_2 = v_sub(v_mult_scal(cb,clamp(prod_scal(cb,pb)/prod_scal(cb,cb),0.0,1.0)),pb);
            vector v_3 = v_sub(v_mult_scal(ac,clamp(prod_scal(ac,pc)/prod_scal(ac,ac),0.0,1.0)),pc);
            float d_1 = prod_scal(v_1,v_1);
            float d_2 = prod_scal(v_2,v_2);
            float d_3 = prod_scal(v_3,v_3);
            return (MIN(MIN(d_1,d_2),d_3));
    }
    else{
        return (prod_scal(nor,pa)*prod_scal(nor,pa)/prod_scal(nor,nor));
    }
}








// SDF du plan horizontal (sol)
float SDF_plan(coord p, vector n, float h){
    vector v = {p.x, p.y, p.z};
    return prod_scal(v,n) - h;
}


// SDF d'une elliposïde
float SDF_Ellipsoid(coord p, coord centre, float a, float b, float c){
    float distx = p.x - centre.x;
    float disty = p.y - centre.y;
    float distz = p.z - centre.z;
    return sqrt((distx*distx) / (a*a) + (disty * disty) / (b*b) + (distz * distz) / (c*c)) - 1.0;
}



// --- NUUUUT NUUUUT --- //

// Tête 
float SDF_head(coord p, coord centre, float rayon){
    float Contour = SDF_sphere(p, centre, rayon);

    coord C_oeG = {centre.x - (rayon/4), centre.y - rayon,centre.z + (rayon/3)};
    float oeilGa = SDF_sphere(p, C_oeG, rayon/6);
    float oeilGauche = SmoothSubstractSDF(Contour, oeilGa, 0.1);


    coord C_oeD = {centre.x + (rayon/4), centre.y - rayon,centre.z + (rayon/3)};
    float oeilDr = SDF_sphere(p, C_oeD, rayon/6);
    float Oeils = SmoothSubstractSDF(oeilGauche, oeilDr, 0.1);

    // coord C_ch1 = {centre.x, centre.y, centre.z + 9*rayon/10};
    // float cheveu1 = SDF_Pyramide(p, C_ch1, (rayon/5), (rayon/20));

    // float Tete = SmoothUnionSDF(oeilGauche, cheveu1, 0.1);
    return Oeils;
}


// Corps
float SDF_corps(coord p, coord centre, float rayon){
    float Contour = SDF_sphere(p, centre, rayon);

    coord C_Bas = {centre.x, centre.y, centre.z - rayon};
    float Bas = SDF_box(p, C_Bas, rayon, rayon, rayon/4);

    float Corps = SmoothSubstractSDF(Contour, Bas, 0.1);

    return Corps;
}


// Total 
float SDF_Pingoo(coord p, coord centre, float rayon){
    coord C_Tete = {centre.x, centre.y, centre.z + rayon/2};
    float Tete = SDF_head(p, C_Tete, 1.1*rayon/2);

    coord C_Corps = {centre.x, centre.y, centre.z - 0.8*rayon/3};
    float Corps = SDF_corps(p, C_Corps, 2.1*rayon/3);

    float Pingoo = SmoothUnionSDF(Tete, Corps, 1);
    return Pingoo;
}




// --- TESTS --- //
float mult_objects(coord pos) {
    // translate
    // float iTime = 1.0;
    
    // pos.x += 0.0;
    // pos.y += 0.0;
    // pos.z += 0.0;

    coord modResult;
    // modResult.x = fmodf(pos.x, 2.0);
    modResult.y = fmodf(pos.y, 2.0);
    modResult.x = fmodf(pos.x, 2.0);
    // modResult.y = pos.y;
    // modResult.z = fmodf(pos.z, 2.0);
    modResult.z = pos.z;

    //float d1 = sqrt((modResult.x - 1.0) * (modResult.x - 1.0) + (modResult.y - 1.0) * (modResult.y - 1.0) + (modResult.z - 1.0) * (modResult.z - 1.0)) - 0.54321;
    // float d1 = SDF_box(modResult, (coord){1.0,1.0,1.0}, 0.5,0.5,0.5);
    float d1 = SDF_Tor(modResult, (coord){1.0,1.0,-1}, 0.5, 0.3);
    return d1;
}

float fractal_1_test(coord z) {
    coord a1 = {1.0, 1.0, 1.0};
    coord a2 = {-1.0, -1.0, 1.0};
    coord a3 = {1.0, -1.0, -1.0};
    coord a4 = {-1.0, 1.0, -1.0};
    coord c;
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
coord rotation_x (coord v, float angle){// angle en degres
    return (coord){v.x, v.y*cos(angle*3.14/180) - v.z*sin(angle*3.14/180), v.y*sin(angle*3.14/180) + v.z*cos(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
coord rotation_y (coord v, float angle){// angle en degres
    return (coord){v.x*cos(angle*3.14/180) + v.z*sin(angle*3.14/180), v.y, v.z*cos(angle*3.14/180) - v.x*sin(angle*3.14/180)};
}

// renvoie le produit entre la matrice de rotation Rx et le vec v
coord rotation_z (coord v, float angle){// angle en degres
    return (coord){v.x*cos(angle*3.14/180) - v.y*sin(angle*3.14/180), v.x*sin(angle*3.14/180) + v.y*cos(angle*3.14/180), v.z};
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




