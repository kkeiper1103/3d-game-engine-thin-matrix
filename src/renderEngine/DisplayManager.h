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
    static int width;
    static int height;

    static const int FPS_CAP = 120;

    static long lastFrameTime;
    static float delta;

    static bool fullscreen;

    static SDL_Window* window;
    static SDL_GLContext gl;

    static long getCurrentTime();

public:
    static void createDisplay();
    static void updateDisplay();
    static void closeDisplay();

    static inline float getFrameTimeSeconds() {
        return delta;
    }
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_DISPLAYMANAGER_H
