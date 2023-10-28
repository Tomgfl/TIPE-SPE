#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dessin_fct.h"
#include "options.h"


void display(){
    // utile ???
    glClear(GL_COLOR_BUFFER_BIT);
    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);
    // glViewport(0, 0, width, height);

    // int b = 0;
    // for (int i = 0; i < WIDTH; i++){
    //     draw_pixel(i,10,0,0,b,10);
    //     b++;
    //     b = b%256;
        
    // }
    
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

    /* Boucle principale */
    while (!glfwWindowShouldClose(window)){
        
        // Affichage
        // display();
        glClear(GL_COLOR_BUFFER_BIT);
        
        // pour tester un peu les fonctions
        //draw_pixel(rand()%WIDTH, rand()%HEIGHT, rand()%255, rand()%255, rand()%255, rand()%100);
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                draw_pixel(i, j, rand()%255, rand()%255, rand()%255, 1);
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
