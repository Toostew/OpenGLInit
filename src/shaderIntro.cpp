//
// Created by tooka on 14/04/2026.
//

#include "../include/shaderIntro.h"

#include <iostream>
#include <glad/glad.h>


//this function outputs the max number of allowed vertex attributes we can use for shaders
//these attribute count is limited by hardware
void shaderIntro::checkMaxVertexVars() {
    int numVertexAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttributes); //binds an int value from the openGL state machine to a var you can use in cpp
    std::cout << numVertexAttributes << std::endl;

}

int shaderIntro::shaderMake() {

    //In GLSL, we can expect the same types of variables like int, uint, bool, float, double
    //there is also 2 special container type variables called vectors and matrices
    //vectors are represented as vecN, where N is the number of components that make up the vector, up to 4
    //you can access these sub components via vector.x, .y, .z, .w, to access the first, second third.. you get it
    


    return 0;
}
