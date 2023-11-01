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
color c_fond = {3,27,73};


// renvoie la lumiere avec le prod vect et la normale
float light_diffuse(coord pts, coord source){
    vector v_n = normalise_vecteur(vect_normal(pts));
    float res = max(prod_scal(v_n, normalise_vecteur(get_vec_2_pts(pts,source))),0);
    return res;
}


float all_light(coord pts, coord source){
    float res = 0;
    res += light_diffuse(pts, source);
    res += 0.3; // lumiere ambiante

    return res;
}


// fait un ray marching entre le point et la source de lumiere (pas le plus opti je pense)
float shadow_1(coord pts, coord source){
    vector direction = normalise_vecteur(get_vec_2_pts(pts, source));
    coord position_actuelle = pts;

    float dist_tot = 0.0;
    position_actuelle.x = pts.x + direction.x * dist_tot;
    position_actuelle.y = pts.y + direction.y * dist_tot;
    position_actuelle.z = pts.z + direction.z * dist_tot;

    for (int i = 0; i < MAX_RAY_STEPS/10; i++){ // on s'éloigne de la surface atteinte
        dist_tot += MIN_ALL_SDF(position_actuelle);
        position_actuelle.x = pts.x + direction.x * dist_tot;
        position_actuelle.y = pts.y + direction.y * dist_tot;
        position_actuelle.z = pts.z + direction.z * dist_tot;
    }
    

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = MIN_ALL_SDF(position_actuelle);
        dist_tot += dist;

        if (dist < DIST_MIN*0.01){
            return 0.0;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            return 1.0;
        }

        position_actuelle.x = pts.x + direction.x * dist_tot;
        position_actuelle.y = pts.y + direction.y * dist_tot;
        position_actuelle.z = pts.z + direction.z * dist_tot;
        
    }

    return 1.0;
}



// renvoie la couleur d'un rayon avec le ray marching
color ray_marching(ray r){
    float dist_tot = 0.0;
    coord position_actuelle = r.origine;

    coord Lumiere = {4.0, 5.0, 5.0}; // lumiere mis a la mano

    for (int i = 0; i < MAX_RAY_STEPS; i++){
        
        float dist = MIN_ALL_SDF(position_actuelle);
        dist_tot += dist;

        if (dist < DIST_MIN){ // Si on touche un objet

            float val_light = all_light(position_actuelle, Lumiere);

            float val_shadow = shadow_1(position_actuelle, Lumiere);

            // val_light = 1;
            // val_shadow = 1;

            color res = {150.0*val_light*val_shadow, 150.0*val_light*val_shadow, 15.0*val_light*val_shadow};
            return res;
        }

        if (dist_tot > MAX_TOTAL_LENGHT){ // Si on va trop loin
            return c_fond;
        }
        
        // actualisation du rayon
        position_actuelle.x = r.origine.x + r.direction.x * dist_tot;
        position_actuelle.y = r.origine.y + r.direction.y * dist_tot;
        position_actuelle.z = r.origine.z + r.direction.z * dist_tot;      
    }

    // aucun objet atteint
    return c_fond;
}



struct screen_s{
    
};
typedef struct screen_s screen; 



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
    ////coord cam_c = {0.0, 0.0, 2.0};
    //vector cam_v = {0.0, 1.0, 0.0};

    // L'ecran est definie par 1 pts, une taille de base et un vecteur
    ////coord A = {-2.0, 3.0, 4.0}; // coin en haut a gauche
    ////float longueur_base = 4.0; // longueur de l'ecran
    //coord B = {2.0, 3.0, 3.0};
    ////vector dir_ecran = {0.0, 0.0, 1.0};
    // coord C = {2.0, 3.0, 0.0};
    // coord D = {-2.0, 3.0, 0.0};
    // coord Lumiere = {4.0, 7.0, 5.0};
    ////float de = longueur_base/WIDTH; // "taille du pixel"

    // coord ecran[WIDTH][HEIGHT]; // coordonnes de chaque pixels de l'ecran

    // for (int i = 0; i < WIDTH; i++){
    //     for (int j = 0; j < HEIGHT; j++){
    //         ecran[i][j].x = A.x+ de*i;
    //         ecran[i][j].y = A.y;
    //         ecran[i][j].z = A.z - de*j;
    //     }
    // }

    // ecran 3 devant camera (y)
    // de longueur 6
    // la cam est donc centrée sur l'écran


    // --- V1 ---
    coord cam_c = {0.1 ,-2 ,0.3};
    float l_ecran = 6.0;
    float de = l_ecran / WIDTH; 
    // coord ecran[WIDTH][HEIGHT]; // coordonnes de chaque pixels de l'ecran
    float screen_mid_x = l_ecran/2.0;
    float screen_mid_z = (l_ecran*HEIGHT)/(2.0*WIDTH);
    float screen_dist_y = 3.0;

    // for (int i = 0; i < WIDTH; i++){
    //     for (int j = 0; j < HEIGHT; j++){
    //         ecran[i][j].x = cam_c.x - screen_mid_x + de*i;
    //         ecran[i][j].y = cam_c.y + screen_dist_y;
    //         ecran[i][j].z = cam_c.z + screen_mid_z - de*j;
    //     }
    // }
    // --- V1 ---

    // --- V2 --- pointeurs pour deplacer la cam facilement
    coord* p_cam;
    p_cam = &cam_c;



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

        // z += 0.5;
        // cam_c.z = z;
        // cam_c.x += -1;
        // cam_c.y += -1;

        color ecran_color[WIDTH][HEIGHT];

        // pour chaque pixel de l'ecran
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){

                // chaque rayon part de la camera en direction de chaque pixel(vect normaliser ie ||v|| = 1)
                ray R;
                R.origine = cam_c;
                // comme dans ecran mais calcul direct
                R.direction = normalise_vecteur(get_vec_2_pts(cam_c,(coord){p_cam->x - screen_mid_x + de*i, p_cam->y + screen_dist_y, p_cam->z + screen_mid_z - de*j}));
                

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
