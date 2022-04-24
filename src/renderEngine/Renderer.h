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
protected:
    float FOV = 70;
    float NEAR_PLANE = 0.1f;
    float FAR_PLANE = 1000.f;

    glm::mat4 projectionMatrix;

    void createProjectionMatrix();

public:
    Renderer(StaticShader& shader);

    void prepare();
    void render(const Entity& entity, StaticShader& shader);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H
