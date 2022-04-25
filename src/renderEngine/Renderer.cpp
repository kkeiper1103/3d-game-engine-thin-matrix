//
// Created by kkeiper on 4/23/2022.
//

#include <cstdio>
#include "Renderer.h"
#include "toolbox/Maths.h"
#include "DisplayManager.h"

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::createProjectionMatrix() {
    float aspectRatio = (float) DisplayManager::width / (float) DisplayManager::height;

    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
}

Renderer::Renderer(StaticShader& shader) : shader(shader) {

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    createProjectionMatrix();

    shader.start();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();

    printf("done starting shader with projection matrix");
}

void Renderer::render(const std::map<TexturedModel, std::vector< EntityPtr >> &entities) {
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

void Renderer::prepareTexturedModel(const TexturedModel& model) {
    auto rawModel = model.getRawModel();

    glBindVertexArray(rawModel.getVao());
    glEnableVertexAttribArray(0); // position attribute
    glEnableVertexAttribArray(1); // textures uv
    glEnableVertexAttribArray(2); // normal

    shader.loadShineVariables(model.getTexture().getShineDamper(), model.getTexture().getReflectivity());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

void Renderer::unbindTexturedModel() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Renderer::prepareInstance(const EntityPtr &entity) {
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
            entity->getPosition(),
            entity->getRotX(), entity->getRotY(), entity->getRotZ(),
            entity->getScale()
    );

    shader.loadTransformationMatrix(transformationMatrix);
}
