//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H

#include <glad/glad.h>

#include "models/RawModel.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "shaders/StaticShader.h"

class Renderer {
public:
    void prepare();
    void render(const Entity& entity, StaticShader& shader);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H
