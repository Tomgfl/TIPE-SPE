#include <GLFW/glfw3.h>
#include <stdio.h>

#include "options.h"

/* Affiche un pixel
x, y : coordonnes du pixel
R,G,B : couleur du pixel
size : taille du point */
void draw_pixel(int x, int y, float R, float G, float B, float size){
    

    glPointSize(size); 
    glBegin(GL_POINTS);
    glColor3f(R/255.0, G/255.0, B/255.0); 

    // Conversion des coordonnes normalisé en classique
    double n_x = (2.0 * x) / WIDTH - 1.0;
    double n_y = 1.0 - (2.0 * y) / HEIGHT;

    // printf("Coordonnées normalisées : (%.2f, %.2f)\n", n_x, n_y);

    glVertex2f(n_x, n_y);
    glEnd();
}


