//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_DISPLAYMANAGER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_DISPLAYMANAGER_H

#include <cstdio>

#include <SDL2/SDL.h>
#include <glad/glad.h>

class DisplayManager {
public:
    const int width = 1280, height = 720;
    bool fullscreen;

    SDL_Window* window = nullptr;
    SDL_GLContext gl = nullptr;

public:
    void createDisplay();
    void updateDisplay();
    void closeDisplay();
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_DISPLAYMANAGER_H
