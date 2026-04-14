//
// Created by tooka on 14/04/2026.
//

#ifndef OPENGLINIT_SHADER_H
#define OPENGLINIT_SHADER_H
#include <string>

//all the implementation logic is already done inside this here header file, not very ideal
//it'll remain for now for educational purposes
class Shader {
public:


    //class constructor needs input for vertex and fragment shaders
    Shader(const char* vertexPath, const char* fragmentPath);


    //activate the shader
    void activateShader();

    //utility uniform functions

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void vertexSetup();

    void drawWithShader();


private:
    //program ID
    unsigned int ID;
    unsigned int globVAO;

};


#endif //OPENGLINIT_SHADER_H