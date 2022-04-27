//
// Created by kkeiper on 4/23/2022.
//

#include <cstdio>
#include "EntityRenderer.h"
#include "toolbox/Maths.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"


EntityRenderer::EntityRenderer(StaticShader& shader, const glm::mat4& projectionMatrix) : shader(shader) {
    shader.start();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();

    printf("done starting shader with projection matrix");
}

void EntityRenderer::render(const std::map<TexturedModel, std::vector< EntityPtr >> &entities) {
    for(auto& kv: entities) {
        auto model = kv.first;

        prepareTexturedModel(model);

        // can't alias kv.second into "batch" as it uses a deleted method (destructor on unique_ptr)
        for(auto& entity: kv.second) {
            prepareInstance(entity);

            glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, nullptr);
        }

        unbindTexturedModel();
    }
}

void EntityRenderer::prepareTexturedModel(const TexturedModel& model) {
    auto rawModel = model.getRawModel();

    glBindVertexArray(rawModel.getVao());
    glEnableVertexAttribArray(0); // position attribute
    glEnableVertexAttribArray(1); // textures uv
    glEnableVertexAttribArray(2); // normal

    if(model.getTexture().isTransparent()) {
        MasterRenderer::disableCulling();
    }

    shader.loadShineVariables(model.getTexture().getShineDamper(), model.getTexture().getReflectivity());
    shader.loadFakeLighting(model.getTexture().isFakeLighting());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

void EntityRenderer::unbindTexturedModel() {
    MasterRenderer::enableCulling();

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(const EntityPtr &entity) {
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
            entity->getPosition(),
            entity->getRotX(), entity->getRotY(), entity->getRotZ(),
            entity->getScale()
    );

    shader.loadTransformationMatrix(transformationMatrix);
}
