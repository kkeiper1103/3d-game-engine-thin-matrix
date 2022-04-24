//
// Created by kkeiper on 4/23/2022.
//

#include <cstdio>
#include "Renderer.h"
#include "toolbox/Maths.h"

void Renderer::prepare() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Entity& entity, StaticShader& shader) {
    auto texturedModel = entity.getModel();
    auto model = texturedModel.getRawModel();

    glBindVertexArray(model.getVao());
    glEnableVertexAttribArray(0); // position attribute
    glEnableVertexAttribArray(1); // textures uv

    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
        entity.getPosition(),
        entity.getRotX(), entity.getRotY(), entity.getRotZ(),
        entity.getScale()
    );

    shader.loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());

    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}
