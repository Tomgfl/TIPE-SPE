#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "dessin_fct.h"
#include "options.h"
#include "signed_distance_function.h"
#include "vector.h"
#include "utiles.h"



struct color_s{
    int r, g, b;
};
typedef struct color_s color;

color c_rouge = {255,0,0};
color c_bleu = {0,0,255};
color c_vert = {0,255,0};
color c_noir = {0,0,0};
color c_blanc = {255,255,255};
color c_gris = {63, 63, 63};

// renvoie la lumiere avec le prod vect et la normale
float light_diffuse(coord pts, coord source){
    vector v_n = normalise_vecteur(vect_normal(pts));
    float res = max(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
    return res;
}





// renvoie la couleur d'un rayon avec le ray marching
color ray_marching(ray r){
    float dist_tot = 0.0;
    coord position_actuelle = r.origine;

    coord Lumiere = {4.0, 7.0, 5.0}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = MIN_ALL_SDF(position_actuelle);
        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet
            // partie lumiere (formules comme ca sont moche, c'est a refaire)
            float light;
            float diffuse = light_diffuse(position_actuelle, Lumiere) *0.5;
            float ambiante = 0.3;
            // le 0.3, 0.7 et 50.0 sont mis de maniere random, c'est a ajuster

            vector lum_direction = get_vec_2_pts(Lumiere,position_actuelle);
            lum_direction.x *= -1.0; lum_direction.y *= -1.0; lum_direction.z *= -1.0;
            // float specular = pow(max(prod_scal(lum_direction,vect_normal(position_actuelle)),0.0),1);

            
            light = diffuse + ambiante;

            color res = {35.0 * light, 200.0 * light, 100.0*light};
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            return c_noir;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    return c_noir;
}






void display(){
    // utile ???
    glClear(GL_COLOR_BUFFER_BIT);  
}


int main(){
    srand(time(NULL));

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){return -1;}

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Test 1", NULL, NULL);
    if (!window){glfwTerminate();return -1;}

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    // cf voir geogebra
    coord cam_c = {0.0, 0.0, 0.0};
    vector cam_v = {0.0, 1.0, 0.0};

    coord A = {-2.0, 3.0, 3.0};
    coord B = {2.0, 3.0, 3.0};
    coord C = {2.0, 3.0, 0.0};
    coord D = {-2.0, 3.0, 0.0};

    // coord Lumiere = {4.0, 7.0, 5.0};

    float dxe = 4.0/640.0;
    float dze = 3.0/480.0;

    coord ecran[WIDTH][HEIGHT]; // coordonnes de chaque pixels de l'ecran

    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran[i][j].x = -2.0 + dxe*i;
            ecran[i][j].y = 3.0;
            ecran[i][j].z = 3.0 - dze*j;
        }
    }



    // printf("(%f,%f,%f) \n",ecran[0][0].x,     ecran[0][0].y,     ecran[0][0].z);
    // printf("(%f,%f,%f) \n",ecran[639][0].x,   ecran[639][0].y,   ecran[639][0].z);
    // printf("(%f,%f,%f) \n",ecran[0][479].x,   ecran[0][479].y,   ecran[0][479].z);
    // printf("(%f,%f,%f) \n",ecran[639][479].x, ecran[639][479].y, ecran[639][479].z);
    

    /* Boucle principale */
    while (!glfwWindowShouldClose(window)){
        
        // Affichage
        // display();
        glClear(GL_COLOR_BUFFER_BIT);
        
        // pour tester un peu les fonctions
        //draw_pixel(rand()%WIDTH, rand()%HEIGHT, rand()%255, rand()%255, rand()%255, rand()%100);
        // for (int i = 0; i < WIDTH; i++){
        //     for (int j = 0; j < HEIGHT; j++){
        //         draw_pixel(i, j, rand()%255, rand()%255, rand()%255, 1);
        //     }  
        // }

        
        color ecran_color[WIDTH][HEIGHT];

        // pour chaque pixel de l'ecran
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){

                // chaque rayon part de la camera en direction de chaque pixel(vect normaliser ie ||v|| = 1)
                ray R;
                R.origine = cam_c;
                R.direction = normalise_vecteur(get_vec_2_pts(cam_c,ecran[i][j]));
                

                color C = ray_marching(R);
                draw_pixel(i, j, C.r, C.g, C.b, 1); // affiche le pixel


            }
        }
        
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
