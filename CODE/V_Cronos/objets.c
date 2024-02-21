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
    obj.rayon = R;
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
    obj.rayon = MAX(L, MAX(l,h))/2; 
    obj.centre = centre;
    return obj;
}

OBJET BuildTriangle (vector a, vector b, vector c, color couleur) {
    OBJET obj;
    obj.type = 6; // Type "5" pour une boîte
    obj.param = malloc(sizeof(param_triangle)); // Allouer de la mémoire pour les paramètres de la boîte
    ((param_triangle*)obj.param)->a = a;  // Longueur de la boîte
    ((param_triangle*)obj.param)->b = b;  // Largeur de la boîte
    ((param_triangle*)obj.param)->c = c;  // Hauteur de la boîte
    obj.couleur = couleur;
    obj.rayon = 2;
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
    obj.rayon = MAX(a, MAX(b,c))/2; 
    obj.centre = centre;
    return obj;
}

void FreeObj (OBJET obj) {
    free(obj.param);
}