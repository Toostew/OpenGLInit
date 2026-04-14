//
// Created by tooka on 14/04/2026.
//

#ifndef OPENGLINIT_SHADERINTRO_H
#define OPENGLINIT_SHADERINTRO_H


class shaderIntro {
public:
    void checkMaxVertexVars();
    void customShader();
    void draw();
    unsigned int getGlobVAO();
    unsigned int getGlobShaderProgram();

private:
    unsigned int globShaderProgram;
    unsigned
    int globVAO;

    const char *vertexShaderSource =
    "#version 330 core\n"
    //the layout (location = 0), you can imagine it as a http port. different port can handle different data
    //in this instance, the port at location 0 specifically is for vector3 coords.
    //if you wanted to handle more types of data, you need to be able to "slice" it up into parts and send them
    //to the appropriate locations (ports).
    //we do this in the glVertexAttribPointer() function call
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 colourAttrib;\n"
    "out vec3 outputColour;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   outputColour = colourAttrib;\n"
    "}\0";


    const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 outputColour;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outputColour,1.0);\n"
    "}\0";


};


#endif //OPENGLINIT_SHADERINTRO_H