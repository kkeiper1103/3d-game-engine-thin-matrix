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
#include <glm/glm.hpp>

class ShaderProgram {
protected:
    unsigned int programID;
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    int loadShader(const std::string& filename, int type);

    virtual void bindAttributes() {};

    void bindAttribute(int attribute, const std::string& variableName);

    int getUniformLocation(const std::string& uniformName);
    virtual void getAllUniformLocations() {};


    void loadInt(int location, int value) {
        glUniform1i(location, value);
    }

    void loadFloat(int location, float value) {
        glUniform1f(location, value);
    }

    void loadVector(int location, const glm::vec3& vec) {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void loadBoolean(int location, bool value) {
        glUniform1i(location, (int) value);
    }

    void loadMatrix(int location, const glm::mat4& mat) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }

public:
    ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);

    inline void start() const {
        glUseProgram(programID);
    }

    inline void stop() const {
        glUseProgram(0);
    }

    void cleanUp();
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_SHADERPROGRAM_H
