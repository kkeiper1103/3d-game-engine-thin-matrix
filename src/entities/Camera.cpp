//
// Created by kkeiper on 4/24/2022.
//

#include "Camera.h"

Camera::Camera() {

}

const glm::vec3 &Camera::getPosition() const {
    return position;
}

float Camera::getPitch() const {
    return pitch;
}

float Camera::getYaw() const {
    return yaw;
}

float Camera::getRoll() const {
    return roll;
}


void Camera::move() {
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);

    if(keys[SDL_SCANCODE_W])
        position.z -= 0.5f;

    if(keys[SDL_SCANCODE_D])
        position.x += 0.5f;

    if(keys[SDL_SCANCODE_A])
        position.x -= 0.5f;

    if(keys[SDL_SCANCODE_S]) {
        position.z += 0.5f;
    }
}
