//
// Created by kkeiper on 4/28/2022.
//

#include "Player.h"
#include "renderEngine/DisplayManager.h"

Player::Player(const TexturedModel& model, const glm::vec3 &position) :
Entity( model, position, 0, 0, 0, 1 ) {

}

void Player::move(const TerrainPtr& terrainPtr) {
    checkInputs();

    increaseRotation(0, currentTurnSpeed * DisplayManager::getFrameTimeSeconds(), 0);

    float distance = currentSpeed * DisplayManager::getFrameTimeSeconds();

    float dx = distance * sin(glm::radians(rotY));
    float dz = distance * cos(glm::radians(rotY));

    increasePosition(dx, 0, dz);

    upwardSpeed += GRAVITY * DisplayManager::getFrameTimeSeconds();
    increasePosition(0, upwardSpeed * DisplayManager::getFrameTimeSeconds(), 0);

    float terrainHeight = terrainPtr->getHeightOfTerrain(position.x, position.z);

    if(getPosition().y < terrainHeight) {
        upwardSpeed = 0;
        position.y = terrainHeight;

        onGround = true;
    }
}

void Player::checkInputs() {
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_W]) {
        currentSpeed = RUN_SPEED;
    }
    else if(keys[SDL_SCANCODE_S]) {
        currentSpeed = -RUN_SPEED;
    }
    else {
        currentSpeed = 0;
    }

    if(keys[SDL_SCANCODE_A]) {
        currentTurnSpeed = TURN_SPEED;
    }
    else if(keys[SDL_SCANCODE_D]) {
        currentTurnSpeed = -TURN_SPEED;
    }
    else {
        currentTurnSpeed = 0;
    }

    if(keys[SDL_SCANCODE_SPACE] && onGround) {
        jump();
    }
}

void Player::jump() {
    upwardSpeed = JUMP_POWER;
    onGround = false;
}
