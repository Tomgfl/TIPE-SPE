#include "objets.h"

#include <stdlib.h>
#include <stdbool.h>


OBJET BuildSphere (vector centre, float r, color couleur) {
    OBJET obj;
    obj.type = 0; // Type "0" pour une sphère
    obj.param = malloc(sizeof(param_sphere)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_sphere*)obj.param)->centre = centre;  // Centre de la sphère
    ((param_sphere*)obj.param)->rayon = r;  // Rayon de la sphère
    obj.couleur = couleur;
    obj.rayon = r;
    obj.centre = centre;
    return obj;
}

OBJET BuildTor (vector centre, float R, float r, color couleur) {
    OBJET obj;
    obj.type = 1; // Type "0" pour une sphère
    obj.param = malloc(sizeof(param_tor)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_tor*)obj.param)->centre = centre;  // Rayon de la sphère
    ((param_tor*)obj.param)->R = R; 
    ((param_tor*)obj.param)->r = r;
    obj.couleur = couleur;
    obj.rayon = R+r;
    obj.centre = centre;
    return obj;
}

OBJET BuildCylindre (vector centre, float H, float r, color couleur) {
    OBJET obj;
    obj.type = 2; // Type "0" pour une sphère
    obj.param = malloc(sizeof(param_cylindre)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_cylindre*)obj.param)->centre = centre;  // Rayon de la sphère
    ((param_cylindre*)obj.param)->H = H; 
    ((param_cylindre*)obj.param)->r = r;
    obj.couleur = couleur;
    obj.rayon = MAX(H/2, r);
    obj.centre = centre;
    return obj;
}

OBJET BuildCone (vector centre, float H, float r, color couleur) {
    OBJET obj;
    obj.type = 3; // Type "0" pour une sphère
    obj.param = malloc(sizeof(param_cone)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_cone*)obj.param)->centre = centre;  // Rayon de la sphère
    ((param_cone*)obj.param)->H = H; 
    ((param_cone*)obj.param)->r = r;
    obj.couleur = couleur;
    obj.rayon = MAX(H, r);
    obj.centre = centre;
    return obj;
}

OBJET BuildPyramide (vector centre, float H, float c, color couleur) {
    OBJET obj;
    obj.type = 4; // Type "0" pour une sphère
    obj.param = malloc(sizeof(param_pyramide)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_pyramide*)obj.param)->centre = centre;  // Rayon de la sphère
    ((param_pyramide*)obj.param)->H = H; 
    ((param_pyramide*)obj.param)->c = c;
    obj.couleur = couleur;
    obj.rayon = MAX(H, c);
    obj.centre = centre;
    return obj;
}

OBJET BuildBox (vector centre, float L, float l, float h, color couleur) {
    OBJET obj;
    obj.type = 5; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_box)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_box*)obj.param)->centre = centre;  // Centre de la boîte
    ((param_box*)obj.param)->L = L;  // Longueur de la boîte
    ((param_box*)obj.param)->l = l;  // Largeur de la boîte
    ((param_box*)obj.param)->h = h;  // Hauteur de la boîte
    obj.couleur = couleur;
    obj.rayon = sqrt(L*L + l*l + h*h); 
    obj.centre = centre;
    return obj;
}

OBJET BuildTriangle (vector a, vector b, vector c, color couleur) {
    OBJET obj;
    obj.type = 6; // Type "6" pour un triangle
    obj.param = malloc(sizeof(param_triangle)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_triangle*)obj.param)->a = a;  // Longueur de la boîte
    ((param_triangle*)obj.param)->b = b;  // Largeur de la boîte
    ((param_triangle*)obj.param)->c = c;  // Hauteur de la boîte
    obj.couleur = couleur;
    
    vector ab = v_sub(b,a);
    vector bc = v_sub(c,b);
    vector ac = v_sub(c,a);
    vector n = prod_vect(ab,bc);
    vector vi = prod_vect(n,ab);
    vector vj = prod_vect(n,ac);
    vector I = v_add(a,v_mult_scal(ab,0.5)); 
    vector J = v_add(a,v_mult_scal(ac,0.5));
    res_systeme_2 inter_1 = solve_systeme_2(vi.x, -vj.x, vi.y, -vj.y, J.x - I.x, J.y - I.y);
    res_systeme_2 inter_2 = solve_systeme_2(vi.y, -vj.y, vi.z, -vj.z, J.y - I.y, J.z - I.z);
    res_systeme_2 inter_3 = solve_systeme_2(vi.x, -vj.x, vi.z, -vj.z, J.x - I.x, J.z - I.z);
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
    
    obj.rayon = norm_vector(v_sub(a,C_s_1));
    obj.centre = a;
    return obj;
}

OBJET BuildEllipsoid (vector centre, float a, float b, float c, color couleur) {
    OBJET obj;
    obj.type = 7; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_ellipsoid)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_ellipsoid*)obj.param)->centre = centre;  // Centre de la boîte
    ((param_ellipsoid*)obj.param)->a = a;  // Longueur de la boîte
    ((param_ellipsoid*)obj.param)->b = b;  // Largeur de la boîte
    ((param_ellipsoid*)obj.param)->c = c;  // Hauteur de la boîte
    obj.couleur = couleur;
    obj.rayon = MAX(a, MAX(b,c)); 
    obj.centre = centre;
    return obj;
}

OBJET BuildUnion (OBJET a, OBJET b) {
    OBJET obj;
    obj.type = -1; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_opdouble)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_opdouble*)obj.param)->o1 = a;  // Centre de la boîte
    ((param_opdouble*)obj.param)->o2 = b;  // Longueur de la boîte
    obj.couleur = c_noir;
    obj.centre = get_vec_2_pts(a.centre, b.centre);
    obj.rayon = dist_2_pts(obj.centre, a.centre) + MAX(a.rayon, b.rayon); 
    return obj;
}

OBJET BuildIntersect (OBJET a, OBJET b) {
    OBJET obj;
    obj.type = -2; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_opdouble)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_opdouble*)obj.param)->o1 = a;  // Centre de la boîte
    ((param_opdouble*)obj.param)->o2 = b;  // Longueur de la boîte
    obj.couleur = c_noir;
    if (a.rayon < b.rayon){
        obj.centre = a.centre;
        obj.rayon = a.rayon; 
    }   else {
        obj.centre = b.centre;
        obj.rayon = b.rayon;
    }
    return obj;
}

OBJET BuildSubstract (OBJET a, OBJET b) {
    OBJET obj;
    obj.type = -3; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_opdouble)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_opdouble*)obj.param)->o1 = a;  // Centre de la boîte
    ((param_opdouble*)obj.param)->o2 = b;  // Longueur de la boîte
    obj.couleur = a.couleur;
    obj.centre = a.centre;
    obj.rayon = a.rayon; 
    return obj;
}

OBJET BuildRotX (OBJET a, float angle) {
    OBJET obj;
    obj.type = -7; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_opsimple)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_opsimple*)obj.param)->o1 = a;  // Centre de la boîte
    ((param_opsimple*)obj.param)->k = angle;  // Longueur de la boîte
    obj.couleur = a.couleur;
    obj.centre = a.centre;
    obj.rayon = a.rayon; 
    return obj;
}

OBJET BuildRotY (OBJET a, float angle) {
    OBJET obj;
    obj.type = -8; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_opsimple)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_opsimple*)obj.param)->o1 = a;  // Centre de la boîte
    ((param_opsimple*)obj.param)->k = angle;  // Longueur de la boîte
    obj.couleur = a.couleur;
    obj.centre = a.centre;
    obj.rayon = a.rayon; 
    return obj;
}

OBJET BuildRotZ (OBJET a, float angle) {
    OBJET obj;
    obj.type = -9; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_opsimple)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_opsimple*)obj.param)->o1 = a;  // Centre de la boîte
    ((param_opsimple*)obj.param)->k = angle;  // Longueur de la boîte
    obj.couleur = a.couleur;
    obj.centre = a.centre;
    obj.rayon = a.rayon; 
    return obj;
}

void FreeObj (OBJET obj) {
    free(obj.param);
}