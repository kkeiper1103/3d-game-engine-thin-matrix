//
// Created by kkeiper on 4/23/2022.
//

#include "ShaderProgram.h"

int ShaderProgram::loadShader(const std::string &filename, int type) {
    using namespace std;

    ifstream file(filename);
    if(!file.is_open()) {
        
    }

    string shaderSource;

    copy(istreambuf_iterator<char>(file),
         istreambuf_iterator<char>(),
         back_inserter(shaderSource));

    file.close();

    const char* text = shaderSource.c_str();
    unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &text, NULL);
    glCompileShader(shaderID);

    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    return shaderID;
}

ShaderProgram::ShaderProgram(const std::string &vertexFile, const std::string &fragmentFile) {
    vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    // I don't think this will ever call (Derived Class)::bindAttributes()
    bindAttributes();
    glLinkProgram(programID);

    glValidateProgram(programID);
}

void ShaderProgram::cleanUp() {
    stop();

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(int attribute, const std::string &variableName) {
    glBindAttribLocation(programID, attribute, variableName.c_str());
}
