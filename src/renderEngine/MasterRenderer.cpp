//
// Created by kkeiper on 4/25/2022.
//

#include "MasterRenderer.h"
#include "DisplayManager.h"

#include <glm/gtc/matrix_transform.hpp>

MasterRenderer::MasterRenderer() : renderer(EntityRenderer(shader, glm::mat4(1.0)) ), terrainRenderer(terrainShader, glm::mat4(1.0)) {
    enableCulling();

    createProjectionMatrix();

    renderer = EntityRenderer(shader, projectionMatrix);
    terrainRenderer = TerrainRenderer(terrainShader, projectionMatrix);
}

void MasterRenderer::cleanUp() {
    shader.cleanUp();
    terrainShader.cleanUp();
}

void MasterRenderer::render(const Light &sun, const Camera &camera) {
    prepare();

    shader.start();
    shader.loadSkyColor(skyColor.r, skyColor.g, skyColor.b);

    shader.loadLight(sun);
    shader.loadViewMatrix(camera);

    renderer.render(entities);

    shader.stop();

    terrainShader.start();
    terrainShader.loadSkyColor(skyColor.r, skyColor.g, skyColor.b);

    terrainShader.loadLight(sun);
    terrainShader.loadViewMatrix(camera);
    terrainRenderer.render(terrains);
    terrainShader.stop();

    //
    terrains.clear();
    entities.clear();
}

void MasterRenderer::processEntity(EntityPtr &entity) {

    // this allows us to check for nullptr instead of crashing on null memory
    auto entityModel = &entity->getModel();

    // if the entityModel is null (doesn't exist), just return. In effect, this allows the program to *not crash*
    // when an empty list of entities is passed to it
    if(entityModel == nullptr) return;

    // much simpler than java; we don't have to worry about creating the new array list, or if it's found or anything,
    // as it just exists due to the declaration

    // also, we do *not* move the entity here, as that would cause it to be deleted when the renderer clears its
    // list of entities at the end of each frame. This creates a copy of the model which is then destroyed at the end
    // of the rendering pass
    entities[*entityModel].push_back( entity );
}


void MasterRenderer::prepare() {
    glEnable(GL_DEPTH_TEST);

    // give the render background a blueish hue to mimic the sky
    glClearColor(skyColor.r, skyColor.g, skyColor.b, skyColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void MasterRenderer::createProjectionMatrix() {
    float aspectRatio = (float) DisplayManager::width / (float) DisplayManager::height;

    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void MasterRenderer::processTerrain(TerrainPtr &terrain) {
    // this allows us to check for nullptr instead of crashing on null memory
    auto terrainModel = &terrain->getModel();

    // if the entityModel is null (doesn't exist), just return. In effect, this allows the program to *not crash*
    // when an empty list of entities is passed to it
    if(terrainModel == nullptr) return;

    // much simpler than java; we don't have to worry about creating the new array list, or if it's found or anything,
    // as it just exists due to the declaration

    // also, we do *not* move the entity here, as that would cause it to be deleted when the renderer clears its
    // list of entities at the end of each frame. This creates a copy of the model which is then destroyed at the end
    // of the rendering pass
    terrains.push_back(terrain);
}
