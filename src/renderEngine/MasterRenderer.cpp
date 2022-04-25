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

    // this allows us to check for nullptr instead of crashing on null memory
    auto entityModel = &entity->getModel();

    // if the entityModel is null (doesn't exist), just return. In effect, this allows the program to *not crash*
    // when an empty list of entities is passed to it
    if(entityModel == nullptr) return;

    // much simpler than java; we don't have to worry about creating the new array list, or if it's found or anything,
    // as it just exists due to the declaration

    // also, we do *not* move the entity here, as that would cause it to be deleted when the renderer clears its
    // list of entities at the end of each frame. This creates a copy of the model which is then destroyed at the end
    // of the rendering pass
    entities[*entityModel].push_back( entity );
}
