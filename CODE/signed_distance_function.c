#include <math.h>
#include <stdio.h>

#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))




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


// SDF du plan horizontal (sol)
float SDF_plan(coord p, vector n, float h){
    vector v = {p.x, p.y, p.z};
    return prod_scal(v,n) - h;
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



