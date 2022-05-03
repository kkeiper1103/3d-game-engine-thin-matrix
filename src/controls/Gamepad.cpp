//
// Created by kkeiper on 5/3/2022.
//

#include "Gamepad.h"

Gamepad::Gamepad(int index) {
    gamepad = SDL_GameControllerOpen(index);


}

Gamepad::~Gamepad() {
    SDL_GameControllerClose(gamepad);
}

void Gamepad::attachTo(Entity *entity) {
    printf( "Requesting to Control Entity with Gamepad...\n" );
    printf( "@todo\n" );

    entity->setController(this);
}

float Gamepad::axis(SDL_GameControllerAxis axis) {
    // need to normalize / remove deadzone
    int amount = SDL_GameControllerGetAxis(gamepad, axis);

    // if the returned amount is less than 10% of the range, we assume the user is not entering input
    if( abs(amount) < (GAMEPAD_MAX_RANGE / 10) ) return 0.f;

    // otherwise, normalize the amount and send it back
    return (float) amount / GAMEPAD_MAX_RANGE;
}

int Gamepad::button(SDL_GameControllerButton button) {
    return SDL_GameControllerGetButton(gamepad, button);
}
