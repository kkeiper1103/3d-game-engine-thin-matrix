#include <iostream>

#include <memory>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderEngine/DisplayManager.h"
#include "renderEngine/Loader.h"
#include "renderEngine/EntityRenderer.h"
#include "shaders/StaticShader.h"
#include "textures/ModelTexture.h"
#include "models/TexturedModel.h"
#include "toolbox/Maths.h"
#include "renderEngine/OBJLoader.h"
#include "renderEngine/MasterRenderer.h"
#include "entities/Player.h"


std::vector<EntityPtr> entities;


/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);


    DisplayManager::createDisplay();
    Loader loader;

    ModelTexture fernTexture( loader.loadTexture("assets/res/fern.png") );
    fernTexture.setTransparent(true);
    TexturedModel fernModel(
        OBJLoader::loadObjModel("assets/res/fern.obj", loader),
        fernTexture
    );

    TexturedModel treeModel(
        OBJLoader::loadObjModel("assets/res/tree.obj", loader),
        ModelTexture( loader.loadTexture("assets/res/tree.png") )
    );

    ModelTexture grassTexture( loader.loadTexture("assets/res/grassTexture.png") );
    grassTexture.setTransparent(true);
    grassTexture.setFakeLighting(true);
    TexturedModel grassModel(
        OBJLoader::loadObjModel("assets/res/grassModel.obj", loader),
        grassTexture
    );


    // generate random amount of trees between 30 and 80
    for(auto i=0; i < (rand() % 50) + 30; i++) {
        float x = 20, y = 0, z = -50, rx = 0, ry = 0, rz = 0, scale = 5.8;

        x = (rand() % 200) - 100;
        z = (rand() % 200) - 230;

        scale = ((rand() / double(RAND_MAX)) + 1) * 5;

        entities.emplace_back( std::make_shared<Entity>(treeModel, glm::vec3(x, y, z), rx, ry, rz, scale) );
    }

    // generate random amount of ferns between 10 and 20
    for(auto i=0; i < (rand() % 10) + 10; i++) {
        float x = 10, y = 0, z = -50, rx = 0, ry = 0, rz = 0, scale = 1;

        x = (rand() % 200) - 100;
        z = (rand() % 200) - 230;

        entities.emplace_back( std::make_shared<Entity>(fernModel, glm::vec3(x, y, z), rx, ry, rz, scale) );
    }

    // generate random amount of grass between 20 and 30
    for(auto i=0; i < (rand() % 10) + 20; i++) {
        float x = 50, y = 0, z = -50, rx = 0, ry = 0, rz = 0, scale = 2;

        x = (rand() % 200) - 100;
        z = (rand() % 200) - 230;

        scale = ((rand() / double(RAND_MAX)) + .5) * 2;

        entities.emplace_back( std::make_shared<Entity>(grassModel, glm::vec3(x, y, z), rx, ry, rz, scale) );
    }


    Light light(glm::vec3( 50, 200, -50 ), glm::vec3( 1, 1, 1 ));


    // terrain generation stuff
    TerrainTexture bg( loader.loadTexture("assets/images/grassy2.png") );
    TerrainTexture rTexture( loader.loadTexture("assets/images/mud.png") );
    TerrainTexture gTexture( loader.loadTexture("assets/images/grassFlowers.png") );
    TerrainTexture bTexture( loader.loadTexture("assets/images/path.png") );
    TerrainTexture blendMap( loader.loadTexture("assets/res/blendMap.png") );

    TerrainTexturePack ttp(bg, rTexture, gTexture, bTexture);


    auto terrain = std::make_shared<Terrain>(0, 0, loader, ttp, blendMap, "assets/images/heightMap.png");
    auto terrain2 = std::make_shared<Terrain>(1, 0, loader, ttp, blendMap, "assets/images/heightMap.png");




    MasterRenderer renderer;
    renderer.createProjectionMatrix();


    // make player
    RawModel playerModel = OBJLoader::loadObjModel("assets/res/lowPolyTree.obj", loader);
    TexturedModel playerTexture(playerModel, ModelTexture(loader.loadTexture("assets/res/lowPolyTree.png")));

    std::shared_ptr<Entity> player = std::make_shared<Player>(playerTexture, glm::vec3(0, 0, 0));

    Camera camera( std::dynamic_pointer_cast<Player>(player) );

    SDL_Event e;
    while(true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto terminate;

            camera.input(&e);
        }

        camera.move();

        std::dynamic_pointer_cast<Player>(player)->move(terrain);

        renderer.processEntity(player);
        renderer.processTerrain(terrain);
        // renderer.processTerrain(terrain2);

        // do ferns and trees
        for(auto& entity: entities) {
            renderer.processEntity(entity);
        }

        renderer.render(light, camera);

        DisplayManager::updateDisplay();
    }
    terminate:


    renderer.cleanUp();
    loader.cleanUp();
    DisplayManager::closeDisplay();

    return 0;
}
