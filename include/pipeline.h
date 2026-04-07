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
private:
    unsigned int globShaderProgram;
    unsigned int globVAO;
};


#endif //OPENGLINIT_PIPELINE_H