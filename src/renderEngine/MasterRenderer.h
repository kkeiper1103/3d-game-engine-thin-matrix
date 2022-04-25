//
// Created by kkeiper on 4/25/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_MASTERRENDERER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_MASTERRENDERER_H

#include <memory>
#include <vector>
#include <map>

#include "shaders/StaticShader.h"
#include "Renderer.h"

class MasterRenderer {
protected:
    StaticShader shader;
    Renderer renderer;

    std::map<TexturedModel, std::vector< EntityPtr >> entities;

public:
    MasterRenderer();

    void render(const Light& sun, const Camera& camera);

    void processEntity(EntityPtr& entity);

    void cleanUp();
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_MASTERRENDERER_H
