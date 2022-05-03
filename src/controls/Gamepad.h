//
// Created by kkeiper on 5/3/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_GAMEPAD_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_GAMEPAD_H

#define GAMEPAD_MAX_RANGE 32767

#include <SDL2/SDL.h>

#include "entities/Entity.h"

class Gamepad {
private:
    SDL_GameController *gamepad = nullptr;



public:
    explicit Gamepad(int index = 0);
    ~Gamepad();

    void attachTo(Entity* entity);


    float axis(SDL_GameControllerAxis axis);
    int button(SDL_GameControllerButton button);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_GAMEPAD_H
