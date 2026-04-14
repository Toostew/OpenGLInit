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
//understand that in graphics, triangles is the fundamental shape that all other shapes are comprised of.
//look up why online shits too long here
float triangleVertices[] = {
    // first triangle
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f,  0.5f, 0.0f,  // top left

};

float squareVertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};










//understand that openGL is a giant state machine, wherein it can only have a finite nuber of results from its configuration. to achieve
//different outputs from the same inputs we need to change its config.
//Think of it as a store. We need to provide what we want, give instructions, fire it up and accept output. all that complexity is abstracted away


int pipeline::shaderConfig() {

    //Vertex Array Object VAO
    //you can think of the VAO as like a recording, we record every action, and then when we save it.
    //the thing is that without VAO we'd have to repeat all the following code, for each object.
    //with VAO it basically repeats everything we've config'd with every new object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);



    //in order for openGL to use our shader we need to pass it over via an object
    //it is referenced by id so we create an int, unsigned (memory address cant be negative)
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    //first arg is the shader object to compile to, second arg is how many strings we're passing as source code
    //third arg is the actual source code, last idek
    //the vertex shader source is the code we are using that we defined above this funciton
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);



    //this is the fragementShader, it is used to figure out the colour output of the pixels
    //notice the source script code can be found above the function
    unsigned int fragmentShaderID;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);

    //the shader program object is the final linked version of multiple shaders combined
    //to use the compiled shaders we made (vertex, fragment) we need to consolidate them here
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID); //vertex
    glAttachShader(shaderProgram, fragmentShaderID); //fragment
    glLinkProgram(shaderProgram); //links them all together

    int success;
    char infolog[1024];



    //check for compile time errors and return the value to success
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success); //check the vertexShader
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &success); //check the fragmentShader
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); //check the shader program



    //since we've linked the shaders they are no longer needed
    //you can destroy them to free up memory
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);




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


    //so far, in order, we've created and compiled our shaders (vertex and fragment)
    //we've linked the 2 shaders into one shader program
    //we've created a VBO to be able to send the vertex data in batches to the GPU
    //we've set all the appropriate infrastructure to allow the VBO to be used (Buffers)


    //before we continue to render something, we need to set how our vertex shader accepts input
    //the vertex shader allows us to process any input we want, but we need to also tell it how to interpret input
    //since we are sending it data as an array of values, we need to split these values into chunks
    //in this example we are only using vector3 coords, so we only need one chunk
    //the first param is the index (location), essentially the port we are using for this data. Maps to a field in the vertex shader
    //second is the size, or the number of sub-values that make up this value. Here, we are sending vector3 data, so XYZ (3)
    //third is the type of data we are sending, here, vector 3 is made up of 3 float values, so it's GL_FLOAT
    //fourth is normalized, meaning should the values be in between 0.0-1.0. since this is position data we set it to false
    //fifth is the stride, in other words the space to get to consecutive, distinct values in the array, measured in bytes
    //since we are sending the data in an array, you can think of the data as (x1,y1,z1,x2,y2,z2,...)
    //the stride is the distance between each distinct vector3 XYZ, so like the distance difference between x1 and x2
    //in this case, each distinct vertex starts every 3 values. to get to the next distinct value, you need to hop the entire size in bytes of the first value
    //the last one is the offset, basically where the start of the specific value type you want is in the array.
    //this is only a big issue if the array you're parsing contains more than one types of data
    //in this example, we are only sending vec3 coords, so it's set to 0 (the weird void* casting idek)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    globShaderProgram = shaderProgram;
    globVAO = VAO;


    return success;
}

//this is the function to demostrate Element Buffer Objects
int pipeline::EBOConfig() {

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);


    //now we create the Element Buffer Objects EBOs, very similar to process of VBOs
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    globShaderProgram = shaderProgram;
    globVAO = VAO;

    return success;
}


void pipeline::draw() {
    glUseProgram(globShaderProgram);
    glBindVertexArray(globVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); //the number of points to draw
}

void pipeline::drawEBO() {
    glUseProgram(globShaderProgram);
    glBindVertexArray(globVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


unsigned int pipeline::getGlobVAO() {
    return globVAO;
}

unsigned int pipeline::getGlobShaderProgram() {
    return globShaderProgram;
}





