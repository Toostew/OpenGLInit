//
// Created by tooka on 04/04/2026.
// To go where many have gone before but few dare enter willingly
//


#include "../include/intro.h"
#include <glad/glad.h>
//glad comes first because it includes the required OpenGL headers
#include <GLFW/glfw3.h>


#include <iostream>

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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Intro", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


}



