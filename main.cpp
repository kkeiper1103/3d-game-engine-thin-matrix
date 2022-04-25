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

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);


    DisplayManager dm;
    dm.createDisplay();


    Loader loader;

    StaticShader shader;
    Renderer renderer(shader);



    RawModel model = OBJLoader::loadObjModel("assets/stall/stall.obj", loader);

    ModelTexture texture( loader.loadTexture("assets/stall/stallTexture.png") );

    TexturedModel texturedModel(model, texture);

    Entity entity(texturedModel, glm::vec3(0, 0, -50), 0, 0, 0, 1);

    Camera camera;



    SDL_Event e;
    while(true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto terminate;
        }

        camera.move();

        renderer.prepare();
        shader.start();

        entity.increaseRotation(0, 1, 0);
        shader.loadViewMatrix(camera);

        renderer.render(entity, shader);

        shader.stop();
        dm.updateDisplay();
    }
    terminate:


    shader.cleanUp();
    loader.cleanUp();
    dm.closeDisplay();

    return 0;
}
