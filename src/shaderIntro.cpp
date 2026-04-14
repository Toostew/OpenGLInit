//
// Created by tooka on 14/04/2026.
//

#include "../include/shaderIntro.h"

#include <iostream>
#include <glad/glad.h>






unsigned int shaderIntro::getGlobShaderProgram() {
    return globShaderProgram;
}

unsigned int shaderIntro::getGlobVAO() {
    return globVAO;
}



//this function outputs the max number of allowed vertex attributes we can use for shaders
//these attribute count is limited by hardware
void shaderIntro::checkMaxVertexVars() {
    int numVertexAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttributes); //binds an int value from the openGL state machine to a var you can use in cpp
    std::cout << numVertexAttributes << std::endl;

}

void shaderIntro::customShader() {

    //In GLSL, we can expect the same types of variables like int, uint, bool, float, double
    //there is also 2 special container type variables called vectors and matrices
    //vectors are represented as vecN, where N is the number of components that make up the vector, up to 4
    //you can access these sub components via vector.x, .y, .z, .w, to access the first, second third.. you get it

    //these vertices have 6 components each, 3 for pos 3 for color
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };



    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
    };



    //init the VAO
    unsigned int VAO; //think of the VAO as a recording that records the configuration state
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //init the vertex shader
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);

    //init the fragment shader
    unsigned int fragmentShaderID;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);

    //consolidate shaders in the shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID); //vertex
    glAttachShader(shaderProgram, fragmentShaderID); //fragment
    glLinkProgram(shaderProgram); //links them all together

    int success;
    char infolog[1024];

    //verify the shaders work
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success); //check the vertexShader
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &success); //check the fragmentShader
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); //check the shader program

    //delete the shaders, we have already combined so these can go
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    //create VBOs
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //now we create the Element Buffer Objects EBOs, very similar to process of VBOs
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //colour
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    globShaderProgram = shaderProgram;
    globVAO = VAO;

}

void shaderIntro::draw() {
    glUseProgram(globShaderProgram);
    glBindVertexArray(globVAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
