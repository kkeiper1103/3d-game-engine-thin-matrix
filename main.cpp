#include <iostream>

#include <memory>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderEngine/DisplayManager.h"
#include "renderEngine/Loader.h"
#include "renderEngine/Renderer.h"
#include "shaders/StaticShader.h"
#include "textures/ModelTexture.h"
#include "models/TexturedModel.h"
#include "toolbox/Maths.h"
#include "renderEngine/OBJLoader.h"
#include "renderEngine/MasterRenderer.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);


    DisplayManager dm;
    dm.createDisplay();
    Loader loader;






    RawModel model = OBJLoader::loadObjModel("assets/models/dragon.obj", loader);
    ModelTexture texture( loader.loadTexture("assets/images/test-tile.png") );

    TexturedModel cubeModel(model, texture);

    Light light(glm::vec3( 3000, 2000, 3000 ), glm::vec3( 1, 1, 1 ));

    Camera camera;


    std::vector<EntityPtr> allCubes;
    for(auto i=0; i < 200; i++) {
        float x = (rand() / double(RAND_MAX)) * 100 - 50;
        float y = (rand() / double(RAND_MAX)) * 100 - 50;
        float z = (rand() / double(RAND_MAX)) * -300;

        // we're using shared instead of unique because these get passed around into the renderer
        // if we used unique_ptr, we'd have to std::move them into the vector within the renderer
        // which is cleared each frame. This will result in the items getting deleted after just
        // one frame of rendering
        auto e = std::make_shared<Entity>(cubeModel, glm::vec3(x, y, z),
          (rand() / double(RAND_MAX)) * 180.f, (rand() / double(RAND_MAX)) * 180.f, (rand() / double(RAND_MAX)) * 180.f,
          1.f);

        // allCubes will *own* the pointers, so we're moving them here, but in processEntity, we do not move them
        allCubes.push_back( std::move(e) );
    }


    MasterRenderer renderer;

    SDL_Event e;
    while(true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto terminate;
        }

        camera.move();


        for(auto& cube: allCubes)
            renderer.processEntity(cube);


        renderer.render(light, camera);

        dm.updateDisplay();
    }
    terminate:

    renderer.cleanUp();
    loader.cleanUp();
    dm.closeDisplay();

    return 0;
}
