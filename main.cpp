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

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);


    DisplayManager dm;
    dm.createDisplay();


    Loader loader;
    Renderer renderer;

    StaticShader shader;


    std::vector<float> vertices = {
        -.5f,  .5f, 0.f,
        -.5f, -.5f, 0.f,
         .5f, -.5f, 0.f,
         .5f,  .5f, 0.f,
    };
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 0, 3
    };
    std::vector<float> textures = {
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
    };


    RawModel model = loader.loadToVAO(vertices, textures, indices);
    ModelTexture texture( loader.loadTexture("assets/images/image.png") );

    TexturedModel texturedModel(model, texture);

    Entity entity(texturedModel, glm::vec3(-1, 0, 0), 0, 0, 0, 1);

    SDL_Event e;
    while(true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto terminate;
        }

        renderer.prepare();
        shader.start();

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
