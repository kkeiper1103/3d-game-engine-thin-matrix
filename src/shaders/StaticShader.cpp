//
// Created by kkeiper on 4/23/2022.
//

#include "StaticShader.h"
#include "toolbox/Maths.h"

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
    location_projectionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
}

void StaticShader::loadTransformationMatrix(const glm::mat4 &matrix) {
    loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(const glm::mat4 &matrix) {
    loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(const Camera &camera) {
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);

    loadMatrix(location_viewMatrix, viewMatrix);
}
