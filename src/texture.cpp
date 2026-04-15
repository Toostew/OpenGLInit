//
// Created by tooka on 14/04/2026.
//

#define STB_IMAGE_IMPLEMENTATION


#include "../include/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/texture.h"
#include "iostream"




void texture::genTexture() {


    //create a texture, bind it to GL_TEXTURE_2D

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture wrapping options (on the currently bound texture object), s, t, r (x,y,z)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //binds the "s" component
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //binds the "t" component

    //the texture filtering options for minifying and magnifying (further or closer)
    //there are a few options but notably GL_NEAREST and GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("HOPDurara(1)(1).jpg", &width, &height, &nrChannels, 0);
    if (!data) {
        std::cout << "Couldn't load image" << std::endl;
    } else {

    //first arg specifies the Texture Target. It tells OpenGL to apply this operation (upload data) to the texture object currently bound to the GL_TEXTURE_2D bind point.
    //second is the mipmap level. Usually, we upload the highest possible LOD and openGL handles downsizing, but you COULD specify smaller sizes
    //third is internalformat, which tells the GPU how to store our image. GL_RGB stores it as RGB values
    //fourth and fifth is width and height, makes sense
    //sixth is border; VERY OLD feature that is essentially dead now. For now (and most likely forever), keep it as 0
    //seven and eight is the format and datatype of the source image; we loaded the image with RGB values and stored as chars (bytes)
    //the last one is the image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //after we call glTextImage2D, the currently bound texture object now has a texture image attached to it. But it only has one base-level image associated with it
    //(the one we initially provided). If we wanted mipmaps without specifying our own files, we can just tell openGL to do it themselves

    //this will generate appropriate mipmaps for all the textures associated with GL_TEXTURE_2D
    glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data); // we are done binding so we can free the image from memory

}

//this function is for testing the vertexes with textures
void texture::textureEBOConfig() {
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
   };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,
        0, 2, 3,
    };



    //init the VAO
    unsigned int VAO; //think of the VAO as a recording that records the configuration state
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    //stride is how far from one point in an attribute to go to another of the same attribute type in another vertex.
    //the last bit with the (void*) is the length we need to travel to reach the first associated value in the vertex.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);
    globVAO = VAO;

}

void texture::drawWithTexture() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}