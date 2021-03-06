//
// Created by kkeiper on 4/23/2022.
//

#include "DisplayManager.h"

int DisplayManager::width = 1280;
int DisplayManager::height = 700;

long DisplayManager::lastFrameTime = 0;
float DisplayManager::delta = 0;

bool DisplayManager::fullscreen = false;

SDL_Window* DisplayManager::window = nullptr;
SDL_GLContext DisplayManager:: gl = nullptr;


void DisplayManager::createDisplay() {
    window = SDL_CreateWindow("GameEngine3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    gl = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl);

    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Unable to load GladGL\n");
        exit(0);
    }

    SDL_GL_SetSwapInterval(1);

    glViewport(0, 0, width, height);

    lastFrameTime = getCurrentTime();
}

void DisplayManager::updateDisplay() {
    SDL_GL_SwapWindow(window);

    long currentFrameTime = getCurrentTime();
    delta = (currentFrameTime - lastFrameTime) / 1000.f; // delta is in seconds

    lastFrameTime = currentFrameTime;
}

void DisplayManager::closeDisplay() {
    SDL_GL_DeleteContext(gl);
    SDL_DestroyWindow(window);
}

long DisplayManager::getCurrentTime() {
    return (long) SDL_GetTicks64();
}
