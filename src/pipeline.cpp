//
// Created by tooka on 05/04/2026.
//

#include "../include/pipeline.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


//the graphics pipeline is a series of procedures for transforming 3D scene into
//a 2D representation on a screen
//You can think of the pipeline as being comprised of individual, distinct units
//of work. They all do distinct functions that eventually add up to produce a finished
//product.
//at it's core, it can be seperated into 3 distinct parts, Application, geometry
//and rasterization
//Application is basically all the other, additional, high-level stuff like collision detection,
//physics atc. Geometry involves the majority of operations involving polygons and their
//vertices. Rasterization converts the 3d representation to a 2D one, to show on screen
//there are many sub-divisions and variations but this it the basic idea

//within openGL, some of the units of work within the graphics pipeline is hardcoded and cant be changed.
//Others can be altered, allowing fine-tuning, and these are called shaders.
//shaders are written in OpenGL Shading Language (GLSL)

//step 1, we need coordinates of something to represent. here, a triangle
//here we list the X, Y and Z coords for 3 points. note the Z coords are 0, so it's 2D
float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";









//understand that openGL is a giant state machine, wherein it can only have a finite nuber of results from its configuration. to achieve
//different outputs from the same inputs we need to change its config.
//Think of it as a store. We need to provide what we want, give instructions, fire it up and accept output. all that complexity is abstracted away


int pipeline::vertexShaderTest() {
    //in order for openGL to use our shader we need to pass it over via an object
    //it is referenced by id so we create an int, unsigned (memory address cant be negative)
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);


    //this is the fragementShader, it is used to figure out the colour output of the pixels
    unsigned int fragmentShaderID;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);

    //the vertexBufferObject VBO stores large nuber of vertices in the GPUs memory
    //a benefit of this is we can send large batches of data to this bugger in gpu memory
    //and keep it there so long as we have memory
    unsigned int vertexBufferObject;

    //we tell openGL that this memory address stores a VBO, id 1
    glGenBuffers(1, &vertexBufferObject);

    //we bind this buffer to the GL_ARRAY_BUFFER, you can think of this as a type of slot
    //since openGL is a state machine it needs a way to accept input
    //these "slots" accept values. GL_ARRAY_BUFFER accepts specifically vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);


    //now we send data into openGL. we specify the target "slot", the size in bites of the data, the data,
    //and the usage. see:
    /*
     *  GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
     *  GL_STATIC_DRAW: the data is set only once and used many times.
     *  GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
     */
    //we use static draw since the data is hardcoded (not gonna change) and we are gonna draw a lot of times
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);


    //first arg is the shader object to compile to, second arg is how many strings we're passing as source code
    //third arg is the actual source code, last idek
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);

    int success;
    char infolog[1024];

    //the shader program object is the final linked version of multiple shaders combined
    //to use the compiled shaders we made (vertex, fragment) we need to consolidate them here
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID); //vertex
    glAttachShader(shaderProgram, fragmentShaderID); //fragment
    glLinkProgram(shaderProgram); //links them all together

    //since we've linked the shaders they are no longer needed
    //you can destroy them to free up memory
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    //check for compile time errors and return the value to success
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    return success;
}





