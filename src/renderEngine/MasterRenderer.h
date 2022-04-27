//
// Created by kkeiper on 4/25/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_MASTERRENDERER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_MASTERRENDERER_H

#include <memory>
#include <vector>
#include <map>

#include "shaders/StaticShader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"

class MasterRenderer {
protected:
    StaticShader shader;
    EntityRenderer renderer;

    TerrainRenderer terrainRenderer;
    TerrainShader terrainShader;

    std::map<TexturedModel, std::vector< EntityPtr >> entities;
    std::vector< TerrainPtr > terrains;

    float FOV = 70;
    float NEAR_PLANE = 0.1f;
    float FAR_PLANE = 1000.f;

    glm::vec4 skyColor = glm::vec4(
        .33, .50, .67, 1
    );

    glm::mat4 projectionMatrix;

public:
    MasterRenderer();


    void prepare();

    void render(const Light& sun, const Camera& camera);

    void processEntity(EntityPtr& entity);
    void processTerrain(TerrainPtr& terrain);

    void cleanUp();


    void createProjectionMatrix();

    static void enableCulling() {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    static void disableCulling() {
        glDisable(GL_CULL_FACE);
    }
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_MASTERRENDERER_H
