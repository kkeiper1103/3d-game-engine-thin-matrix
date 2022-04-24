//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_SHADERPROGRAM_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_SHADERPROGRAM_H

#include<fstream>
#include<iostream>
#include<iterator>
#include<string>

#include <glad/glad.h>

class ShaderProgram {
protected:
    unsigned int programID;
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    int loadShader(const std::string& filename, int type);

    virtual void bindAttributes() {};

    void bindAttribute(int attribute, const std::string& variableName);

public:
    ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);

    inline void start() const {
        glUseProgram(programID);
    }

    inline void stop() const {
        glUseProgram(0);
    }

    void cleanUp();


    void uniform1v(const std::string& name, int value) {
        glUniform1i( glGetUniformLocation(programID, name.c_str()), value );
    }
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_SHADERPROGRAM_H
