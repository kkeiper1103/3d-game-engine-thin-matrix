//
// Created by kkeiper on 4/26/2022.
//

#include "TerrainShader.h"
#include "toolbox/Maths.h"

std::string TerrainShader::vertexFile = "assets/shaders/terrainVertex.glsl";
std::string TerrainShader::fragmentFile = "assets/shaders/terrainFragment.glsl";

void TerrainShader::bindAttributes() {
    // these may have no effect due to the layout syntax within the glsl
    // if I removed the layout blocks within the glsl files, this might not work,
    // as it's relinking the program

    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

TerrainShader::TerrainShader() : ShaderProgram(vertexFile, fragmentFile) {
    bindAttributes();
    getAllUniformLocations();

    glLinkProgram(programID);
}

void TerrainShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation("transformationMatrix");
    location_projectionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
    location_lightColor = getUniformLocation("lightColor");
    location_lightPosition = getUniformLocation("lightPosition");
    location_shineDamper = getUniformLocation("shineDamper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_skyColor = getUniformLocation("skyColor");
}

void TerrainShader::loadTransformationMatrix(const glm::mat4 &matrix) {
    loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(const glm::mat4 &matrix) {
    loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(const Camera &camera) {
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);

    loadMatrix(location_viewMatrix, viewMatrix);
}

void TerrainShader::loadLight(const Light &light) {
    loadVector(location_lightPosition, light.getPosition());
    loadVector(location_lightColor, light.getColor());
}

void TerrainShader::loadShineVariables(float damper, float reflectivity) {
    loadFloat(location_shineDamper, damper);
    loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadSkyColor(float r, float g, float b) {
    loadVector(location_skyColor, glm::vec3(r, g, b));
}
