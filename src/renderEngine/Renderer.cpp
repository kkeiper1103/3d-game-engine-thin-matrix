//
// Created by kkeiper on 4/23/2022.
//

#include <cstdio>
#include "Renderer.h"

void Renderer::prepare() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const TexturedModel &texturedModel) {
    auto model = texturedModel.getRawModel();

    glBindVertexArray(model.getVao());
    glEnableVertexAttribArray(0); // position attribute
    glEnableVertexAttribArray(1); // textures uv

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());

    glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}
