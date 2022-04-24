//
// Created by kkeiper on 4/23/2022.
//

#include "StaticShader.h"

std::string StaticShader::vertexFile = "assets/shaders/vertex.glsl";
std::string StaticShader::fragmentFile = "assets/shaders/fragment.glsl";

void StaticShader::bindAttributes() {
    // these may have no effect due to the layout syntax within the glsl
    // if I removed the layout blocks within the glsl files, this might not work,
    // as it's relinking the program

    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}

StaticShader::StaticShader() : ShaderProgram(vertexFile, fragmentFile) {
    bindAttributes();
    getAllUniformLocations();

    glLinkProgram(programID);
}

void StaticShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation("transformationMatrix");
}

void StaticShader::loadTransformationMatrix(const glm::mat4 &matrix) {
    loadMatrix(location_transformationMatrix, matrix);
}
