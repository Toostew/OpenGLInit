//
// Created by tooka on 05/04/2026.
//

#ifndef OPENGLINIT_PIPELINE_H
#define OPENGLINIT_PIPELINE_H


class pipeline {
public:
    int shaderConfig();
    int EBOConfig();
    void draw();
    void drawEBO();
    unsigned int getGlobShaderProgram();
    unsigned int getGlobVAO();
private:
    unsigned int globShaderProgram;
    unsigned int globVAO;

    const char *vertexShaderSource =
    "#version 330 core\n"
    //the layout (location = 0), you can imagine it as a http port. different port can handle different data
    //in this instance, the port at location 0 specifically is for vector3 coords.
    //if you wanted to handle more types of data, you need to be able to "slice" it up into parts and send them
    //to the appropriate locations (ports).
    //we do this in the glVertexAttribPointer() function call
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 sharedColour;\n"
        "void main()\n"
        "{\n"
        "   FragColor = sharedColour;\n"
        "}\0";
};


#endif //OPENGLINIT_PIPELINE_H