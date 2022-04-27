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
    bindAttribute(2, "normal");
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
    location_lightColor = getUniformLocation("lightColor");
    location_lightPosition = getUniformLocation("lightPosition");
    location_shineDamper = getUniformLocation("shineDamper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_fakeLighting = getUniformLocation("fakeLighting");
    location_skyColor = getUniformLocation("skyColor");
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

void StaticShader::loadLight(const Light &light) {
    loadVector(location_lightPosition, light.getPosition());
    loadVector(location_lightColor, light.getColor());
}

void StaticShader::loadShineVariables(float damper, float reflectivity) {
    loadFloat(location_shineDamper, damper);
    loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadFakeLighting(bool fakeLighting) {
    loadFloat(location_fakeLighting, (float) fakeLighting);
}

void StaticShader::loadSkyColor(float r, float g, float b) {
    loadVector(location_skyColor, glm::vec3(r, g, b));
}
