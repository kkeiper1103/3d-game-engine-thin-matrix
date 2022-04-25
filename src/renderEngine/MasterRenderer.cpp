//
// Created by kkeiper on 4/25/2022.
//

#include "MasterRenderer.h"

MasterRenderer::MasterRenderer() : renderer( Renderer(shader) ) {

}

void MasterRenderer::cleanUp() {
    shader.cleanUp();
}

void MasterRenderer::render(const Light &sun, const Camera &camera) {
    renderer.prepare();
    shader.start();

    shader.loadLight(sun);
    shader.loadViewMatrix(camera);

    renderer.render(entities);

    shader.stop();

    //
    entities.clear();
}

void MasterRenderer::processEntity(EntityPtr &entity) {
    TexturedModel entityModel = entity->getModel();

    // much simpler than java; we don't have to worry about creating the new array list, or if it's found or anything,
    // as it just exists due to the declaration

    // also, we do *not* move the entity here, as that would cause it to be deleted when the renderer clears its
    // list of entities at the end of each frame. This creates a copy of the model which is then destroyed at the end
    // of the rendering pass
    entities[entityModel].push_back( entity );
}
