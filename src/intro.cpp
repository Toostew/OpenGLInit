//
// Created by tooka on 04/04/2026.
// To go where many have gone before but few dare enter willingly
//


#include "../include/intro.h"
#include <glad/glad.h>
//glad comes first because it includes the required OpenGL headers
#include <GLFW/glfw3.h>


#include <iostream>




//openGL is a Hardware Driver API. Since every GPU driver (Nvidia, AMD, Intel)
//stores OpenGL functions at different memory addresses, we can't call them directly.
//GLAD "loads" these function pointers at runtime so we don't have to manually
//query the driver for every single OpenGL version and hardware spec.


//This allows for resizing, when a user resizes the window, the viewport should resize too
//GLFW calls this function, and it will inject the window in question, and the new width and height
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "framebuffer size: " << width << "x" << height << std::endl;
}

void processInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

}

int main() {

    //we initialize GLFW using init
    glfwInit();
    //we can now configure GLFW using window hint
    //the first option in glfwWindowHint is the option we want to change,
    //the second is the value we set it to
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //we create a GLFWwindow object using the glfwCreateWindow function
    //the first 2args are wxh, 3rd is title
    //notice how it's a pointer (stores memory address) and not a reference
    //this is called an Opaque pointer. it acts as an encapsulation and abstraction over the internal code
    //this way, we can't really do anything to it since it's just a pointer,
    //so we really can only do things by passing it back to GLFW, they'll be able to access its content
    GLFWwindow* window = glfwCreateWindow(800, 600, "Intro", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    //GLAD manages funcion pointers for OpenGL so we want to initialize
    //GLAD before we call any OpenGL function

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //we set the function to handle window & viewport resizing.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);
    while(!glfwWindowShouldClose(window)){

        //process input
        processInput(window);


        //in most graphics applications, when drawing an image, it takes time
        //to fill in the pixels where you want them. Because of this, if you only had one buffer
        //to both be printed and displayed, you will see artifacts since the code will have to draw
        //your graphics.
        //So most modern applications have a double buffer, usually a front and back buffer.
        //in the graphics pipeline, the image is printed in the back buffer, unseen by the user
        //once it's done, it's passed to the front buffer, which can be viewed by the user
        //this way, the user will only ever see the finished images in the front buffer
        //the most basic pipeline is that we make changes to the back buffer, and
        //when it's ready, swap it with the front buffer
        //buffers contains coordinates for every single pixel, with their coresponding colours

        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); //

        glfwSwapBuffers(window); //swaps the current front buffer and back buffer
        glfwPollEvents(); //checks if any events were triggered like keyboard input
    }

    glfwTerminate();
    return 0;
}



