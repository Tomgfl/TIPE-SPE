#include "dessin_fct.h"

/* Affiche un pixel
x, y : coordonnes du pixel
R,G,B : couleur du pixel
size : taille du point */
void draw_pixel(int x, int y, color C, float size){

    glPointSize(size); 
    glBegin(GL_POINTS);
    glColor3f(C.r/255.0*C.opp, C.g/255.0*C.opp, C.b/255.0*C.opp); 

    // Conversion des coordonnes normalisé en classique
    double n_x = (2.0 * x) / WIDTH - 1.0;
    double n_y = 1.0 - (2.0 * y) / HEIGHT;

    // printf("Coordonnées normalisées : (%.2f, %.2f)\n", n_x, n_y);

    glVertex2f(n_x, n_y);
    glEnd();
}