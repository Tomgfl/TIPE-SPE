#ifndef OBJETS_H 
#define OBJETS_H


#include "utiles.h"
#include "vector.h"
#include "signed_distance_function.h"
#include "options.h"



OBJET BuildSphere (vector centre, float r, color couleur);
OBJET BuildBox (vector centre, float L, float l, float h, color couleur);
OBJET BuildTor (vector centre, float R, float r, color couleur);
OBJET BuildCylindre (vector centre, float H, float r, color couleur);
OBJET BuildCone (vector centre, float H, float r, color couleur);
OBJET BuildPyramide (vector centre, float H, float c, color couleur);
OBJET BuildTriangle (vector a, vector b, vector c, color couleur);
OBJET BuildEllipsoid (vector centre, float a, float b, float c, color couleur);
OBJET BuildUnion (OBJET a, OBJET b);
OBJET BuildIntersect (OBJET a, OBJET b);
OBJET BuildSubstract (OBJET a, OBJET b);
OBJET BuildRotX (OBJET a, float angle);
OBJET BuildRotY (OBJET a, float angle);
OBJET BuildRotZ (OBJET a, float angle);
void FreeObj (OBJET obj);


#endif