//
// Created by kkeiper on 4/26/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINRENDERER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINRENDERER_H

#include <vector>

#include "shaders/TerrainShader.h"
#include "terrains/Terrain.h"
#include "models/TexturedModel.h"

class TerrainRenderer {
protected:
    TerrainShader shader;


public:
    TerrainRenderer(TerrainShader& shader, const glm::mat4& projectionMatrix);

    void render(const std::vector<TerrainPtr>& terrains);

    void prepareTerrain(const TerrainPtr& model);
    void unbindTexturedModel();
    void loadModelMatrix(const TerrainPtr& entity);

    void bindTextures(const TerrainPtr& terrain);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINRENDERER_H
