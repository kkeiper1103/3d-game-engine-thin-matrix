//
// Created by kkeiper on 4/26/2022.
//

#include "TerrainRenderer.h"
#include "toolbox/Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader &shader, const glm::mat4 &projectionMatrix) : shader(shader) {
    shader.start();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();
}

void TerrainRenderer::render(const std::vector<TerrainPtr> &terrains) {
    for(auto& t: terrains) {
        prepareTerrain(t);
        loadModelMatrix(t);

        glDrawElements(GL_TRIANGLES, t->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);

        unbindTexturedModel();
    }
}

void TerrainRenderer::prepareTerrain(const TerrainPtr& terrain) {
    auto rawModel = terrain->getModel();

    glBindVertexArray(rawModel.getVao());
    glEnableVertexAttribArray(0); // position attribute
    glEnableVertexAttribArray(1); // textures uv
    glEnableVertexAttribArray(2); // normal

    shader.loadShineVariables(terrain->getTexture().getShineDamper(), terrain->getTexture().getReflectivity());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrain->getTexture().getID());
}

void TerrainRenderer::unbindTexturedModel() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(const TerrainPtr &terrain) {
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
            glm::vec3(terrain->getX(), 0, terrain->getZ()),
            0, 0, 0, 1
    );

    shader.loadTransformationMatrix(transformationMatrix);
}