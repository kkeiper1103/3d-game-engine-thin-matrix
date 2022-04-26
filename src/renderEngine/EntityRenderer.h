//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_ENTITYRENDERER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_ENTITYRENDERER_H

#include <map>
#include <vector>
#include <memory>

#include <glad/glad.h>

#include "models/RawModel.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "shaders/StaticShader.h"

class EntityRenderer {
protected:
    StaticShader shader;

public:
    EntityRenderer(StaticShader& shader, const glm::mat4& projectionMatrix);

    void render( const std::map<TexturedModel, std::vector< EntityPtr >>& entities );
    void prepareTexturedModel(const TexturedModel& model);
    void unbindTexturedModel();
    void prepareInstance(const EntityPtr& entity);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_ENTITYRENDERER_H
