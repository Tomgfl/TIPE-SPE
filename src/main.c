#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <float.h>

// --- LIBRAIRIES GRAPHIQUES ---
#include <GL/gl.h> 
#include <GLFW/glfw3.h>

// --- NUKLEAR (GUI) ---
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_glfw_gl2.h"

// --- TES FICHIERS ---
#include "vector.h"
#include "objets.h"
#include "scene.h"
#include "ray_marching.h"
#include "dessin_fct.h"
#include "options.h" 

// Variables Globales
float time_scene = 0.0f;
res_SDF (*My_scene_p)(vector) = NULL;
int GLOBAL_PIXEL_STEP = 1;
stats_opti STATS = {0,0,0,0,0,0.0,0.0,0.0,0.0};

typedef struct {
    OBJET liste[100];
    int count;
    int selected_id;
} SceneEditor;

SceneEditor MyScene = { .count = 0, .selected_id = -1 };

// Wrapper pour lire la scène
res_SDF Scene_Dynamique_Wrapper(vector p) {
    if (MyScene.count == 0) return (res_SDF){1000.0f, c_blanc};
    
    res_SDF min_res = (res_SDF){FLT_MAX, c_blanc};
    for (int i = 0; i < MyScene.count; i++) {
        res_SDF res_obj = SDF_Objet(p, MyScene.liste[i]);
        if (res_obj.dist < min_res.dist) {
            min_res = res_obj;
        }
    }
    return min_res;
}

void AjouterSphereDefaut() {
    if (MyScene.count < MAX_OBJETS) {
        MyScene.liste[MyScene.count] = BuildSphere((vector){0, 0, 0}, 1.0, c_rouge);
        MyScene.count++;
    }
}

int main() {
    // Initialisation GLFW
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Editeur Ray Marching", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // Initialisation Nuklear
    struct nk_context *ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

    // Caméra 
    camera CAMERA;
    CAMERA.size_L_e = 2.0;
    CAMERA.position_c = (vector){-5, 0, 0}; // Position
    CAMERA.dir_ecran_c = normalise_vecteur((vector){1, 0, 0}); // Regarde vers +X
    CAMERA.up_c = normalise_vecteur((vector){0, 0, -1}); // +Z vers le haut
    CAMERA.dist_screen = 2.0;

    // Calculs Vecteurs Caméra
    CAMERA.orthcam = normalise_vecteur(prod_vect(CAMERA.up_c, CAMERA.dir_ecran_c));
    CAMERA.de = CAMERA.size_L_e / WIDTH;
    CAMERA.size_l_e = HEIGHT*CAMERA.de;
    
    CAMERA.A = (vector){
        CAMERA.position_c.x + CAMERA.dist_screen*CAMERA.dir_ecran_c.x + CAMERA.size_l_e/2.0*CAMERA.up_c.x + CAMERA.size_L_e/2.0*CAMERA.orthcam.x,
        CAMERA.position_c.y + CAMERA.dist_screen*CAMERA.dir_ecran_c.y + CAMERA.size_l_e/2.0*CAMERA.up_c.y + CAMERA.size_L_e/2.0*CAMERA.orthcam.y,
        CAMERA.position_c.z + CAMERA.dist_screen*CAMERA.dir_ecran_c.z + CAMERA.size_l_e/2.0*CAMERA.up_c.z + CAMERA.size_L_e/2.0*CAMERA.orthcam.z
    };

    CAMERA.vlde = (vector){-CAMERA.de*CAMERA.up_c.x, -CAMERA.de*CAMERA.up_c.y, -CAMERA.de*CAMERA.up_c.z};
    CAMERA.vLde = (vector){-CAMERA.de*CAMERA.orthcam.x, -CAMERA.de*CAMERA.orthcam.y, -CAMERA.de*CAMERA.orthcam.z};

    // Allocations Mémoire
    ray** ecran_ray = (ray**)malloc(WIDTH*sizeof(ray*));
    color** ecran_res = (color**)malloc(WIDTH*sizeof(color*));
    for (int i = 0; i < WIDTH; i++){
        ecran_ray[i] = (ray*)malloc(HEIGHT*sizeof(ray));
        ecran_res[i] = (color*)malloc(HEIGHT*sizeof(color));
    }

    // Init Rayons
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            ecran_ray[i][j].origine = CAMERA.position_c;
            ecran_ray[i][j].direction = normalise_vecteur(get_vec_2_pts(CAMERA.position_c,
                    (vector){CAMERA.A.x + i*CAMERA.vLde.x + j*CAMERA.vlde.x,
                            CAMERA.A.y + i*CAMERA.vLde.y + j*CAMERA.vlde.y,
                            CAMERA.A.z + i*CAMERA.vLde.z + j*CAMERA.vlde.z}));
        }
    } 

    // Scène et Threads
    AjouterSphereDefaut();
    My_scene_p = Scene_Dynamique_Wrapper;

    // Threads
    vector n_plan = {0, 0, -1}; vector m_plan = {0, 0, -100}; color c_plan  = c_blanc;
    pthread_t* threads = (pthread_t*) malloc(NB_THREADS*sizeof(pthread_t));
    arg* args = (arg*) malloc(NB_THREADS*sizeof(arg));
    for (int i = 0; i < NB_THREADS; i++){
        args[i] = (arg){My_scene_p, NULL, NULL, NULL, i, ecran_ray, ecran_res, n_plan, m_plan, c_plan};
    }

    // --- BOUCLE PRINCIPALE ---
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        nk_glfw3_new_frame();

        int is_interacting = 0;
        if (nk_window_is_any_hovered(ctx) || nk_item_is_any_active(ctx)) {
            is_interacting = 1;
        }

        int pixel_step = is_interacting ? 4 : 1;

        // -- INTERFACE --
        if (nk_begin(ctx, "Inspecteur", nk_rect(WIDTH-300, 0, 300, HEIGHT),
            NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {

            nk_layout_row_dynamic(ctx, 30, 2); // 2 boutons par ligne
            if (nk_button_label(ctx, "Add Sphere")) { // Ajoute une sphère
                AjouterSphereDefaut();
            }
            if (nk_button_label(ctx, "Add Cube")) { // Ajoute un cube
                if (MyScene.count < MAX_OBJETS) {
                    MyScene.liste[MyScene.count] = BuildBox((vector){0, 0, 0}, 1, 1, 1, c_blanc);
                    MyScene.count++;
                }
            }
            if (nk_button_label(ctx, "Add Tor")) { // Ajoute un tor
                if (MyScene.count < MAX_OBJETS) {
                    MyScene.liste[MyScene.count] = BuildTor((vector){0, 0, 0}, 1, 0.2, c_blanc);
                    MyScene.count++;
                }
            }

            nk_layout_row_dynamic(ctx, 10, 1);
            nk_label(ctx, "--------------------", NK_TEXT_CENTERED);

            // Liste Objets
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "Selection:", NK_TEXT_LEFT);

            // Zone déroulante si il y en a beaucoup
            nk_layout_row_dynamic(ctx, 150, 1);
            if (nk_group_begin(ctx, "ListeObjets", NK_WINDOW_BORDER)) {
                nk_layout_row_dynamic(ctx, 18, 1);
                for (int i = 0; i < MyScene.count; ++i) {
                    char buffer[64];
                    const char* type_name = (MyScene.liste[i].type == 0) ? "Sphere" : 
                                            (MyScene.liste[i].type == 5) ? "Box" :
                                            (MyScene.liste[i].type == 1) ? "Tor" : "Objet" ;
                    
                    sprintf(buffer, "%d: %s", i, type_name);
                    
                    if (nk_select_label(ctx, buffer, NK_TEXT_LEFT, MyScene.selected_id == i)) {
                        MyScene.selected_id = i;
                    }
                }
                nk_group_end(ctx);
            }

            // Edition Objets
            if (MyScene.selected_id != -1 && MyScene.selected_id < MyScene.count) {
                OBJET* obj = &MyScene.liste[MyScene.selected_id];
                
                nk_layout_row_dynamic(ctx, 10, 1);
                nk_label(ctx, "--------------------", NK_TEXT_CENTERED);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, "Proprietes:", NK_TEXT_LEFT);

                // Position Objet
                nk_layout_row_dynamic(ctx, 25, 1);
                nk_property_float(ctx, "Pos X", -50.0f, &obj->centre.x, 50.0f, 0.1f, 0.2f);
                nk_property_float(ctx, "Pos Y", -50.0f, &obj->centre.y, 50.0f, 0.1f, 0.2f);
                nk_property_float(ctx, "Pos Z", -50.0f, &obj->centre.z, 50.0f, 0.1f, 0.2f);
                // Couleur Objet
                nk_layout_row_dynamic(ctx, 25, 1);
                nk_label(ctx, "Couleur:", NK_TEXT_LEFT);
                struct nk_colorf gui_color = {obj->couleur.r/255.0f, obj->couleur.g/255.0f, obj->couleur.b/255.0f, 1.0f};
                
                if (nk_combo_begin_color(ctx, nk_rgb_cf(gui_color), nk_vec2(200,400))) {
                    nk_layout_row_dynamic(ctx, 120, 1);
                    gui_color = nk_color_picker(ctx, gui_color, NK_RGBA);
                    obj->couleur.r = gui_color.r * 255.0f;
                    obj->couleur.g = gui_color.g * 255.0f;
                    obj->couleur.b = gui_color.b * 255.0f;
                    nk_combo_end(ctx);
                }

                // Paramètre de l'objet
                if (obj->type == 0) { // Sphere
                    param_sphere* p = (param_sphere*)obj->param;
                    p->centre = obj->centre;
                    nk_layout_row_dynamic(ctx, 25, 1);
                    nk_property_float(ctx, "Rayon", 0.1f, &p->rayon, 20.0f, 0.1f, 0.1f);
                } 
                else if (obj->type == 5) { // Boite
                    param_box* p = (param_box*)obj->param;
                    p->centre = obj->centre; 
                    nk_layout_row_dynamic(ctx, 25, 1);
                    nk_property_float(ctx, "Len X", 0.1f, &p->L, 20.0f, 0.1f, 0.1f);
                    nk_property_float(ctx, "Len Y", 0.1f, &p->l, 20.0f, 0.1f, 0.1f);
                    nk_property_float(ctx, "Len Z", 0.1f, &p->h, 20.0f, 0.1f, 0.1f);
                }
                else if (obj->type == 1) { // Tor
                    param_tor* p = (param_tor*)obj->param;
                    p->centre = obj->centre;
                    nk_layout_row_dynamic(ctx, 25, 1);
                    nk_property_float(ctx, "Rayon", 0.1f, &p->R, 20.0f, 0.1f, 0.1f);
                    nk_property_float(ctx, "Epaisseur", 0.1f, &p->r, 20.0f, 0.1f, 0.1f);
                }
            }

            // DEBUG
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_labelf(ctx, NK_TEXT_LEFT, "FPS Mode: %s", is_interacting ? "Low Res (Fast)" : "High Res");
        }
        nk_end(ctx);
        
        // Ray Marching BVH
        BVHNode* rootFrame = NULL;
        if (MyScene.count > 0) {
            rootFrame = buildBVH(MyScene.liste, MyScene.count); // Construction
        }

        GLOBAL_PIXEL_STEP = pixel_step;
        for (int i = 0; i < NB_THREADS; i++){
            args[i].bvh = rootFrame;
        }

        // Threads
        for (int i = 0; i < NB_THREADS; i++){
            pthread_create(threads+i, NULL, thread_editor_bvh, args+i); 
        }
        for (int i = 0; i < NB_THREADS; i++) pthread_join(threads[i], NULL);

        // Destruction BVH  pour ne pas saturer la RAM !
        if (rootFrame) {
            freeBVH_Editor(rootFrame); // freeBVH détruit les objets
        }        

        // AFFICHAGE
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fond noir
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D); 
        glDisable(GL_BLEND);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Dessin Optimisé
        // Si on est en mode "Low Res", on dessine des gros points pour remplir les trous
        glPointSize((float)pixel_step); 
        
        glBegin(GL_POINTS);
        for (int i = 0; i < WIDTH; i += pixel_step){     // On saute des pixels
            for (int j = 0; j < HEIGHT; j += pixel_step){
                color c = ecran_res[i][j];
                glColor3f(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f);
                glVertex2i(i + pixel_step/2, j + pixel_step/2); 
            }
        }
        glEnd();

        glPointSize(1.0f);
        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(window);
    }

    // Fermeture
    nk_glfw3_shutdown();
    glfwTerminate();

    // Free
    for (int i = 0; i < WIDTH; i++){
        free(ecran_ray[i]);
        free(ecran_res[i]);
    }
    free(ecran_ray);
    free(ecran_res);
    free(args);
    free(threads);

    return 0;
}