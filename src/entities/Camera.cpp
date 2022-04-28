//
// Created by kkeiper on 4/24/2022.
//

#include "Camera.h"

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
    float horizontalDistance = calculateHorizontalDistance();
    float verticalDistance = calculateVerticalDistance();

    calculateCameraPosition(horizontalDistance, verticalDistance);

    yaw = 180 - (player->getRotY() + angleAroundPlayer);
}

Camera::Camera(const glm::vec3 &position) : position(position) {

}

Camera::Camera(const PlayerPtr& player) : player(player) {

}

void Camera::calculateZoom(const SDL_Event *e) {
    if(e->type == SDL_MOUSEWHEEL) {
        float zoomLevel = e->wheel.y;
        distanceFromPlayer -= zoomLevel;
    }
}

void Camera::calculatePitch(const SDL_Event *e) {
    if(e->type == SDL_MOUSEMOTION) {
        // if the right button is pressed during the motion, change the pitch
        if( (e->motion.state & SDL_BUTTON_RMASK) ) {

            float pitchChange = e->motion.yrel * .1f;
            pitch -= pitchChange;
        }
    }
}

void Camera::calculateAngleAroundPlayer(const SDL_Event *e) {
    if(e->type == SDL_MOUSEMOTION) {
        // if the right button is pressed during the motion, change the pitch
        if( (e->motion.state & SDL_BUTTON_LMASK) ) {

            float angleChange = e->motion.xrel * .3f;
            angleAroundPlayer += angleChange;
        }
    }
}

void Camera::input(const SDL_Event *e) {
    calculateZoom(e);
    calculatePitch(e);
    calculateAngleAroundPlayer(e);
}

float Camera::calculateHorizontalDistance() {
    return distanceFromPlayer * (float) cos(glm::radians( pitch ));
}

float Camera::calculateVerticalDistance() {
    return distanceFromPlayer * (float) sin(glm::radians( pitch ));
}

void Camera::calculateCameraPosition(float dx, float dy) {
    float theta = player->getRotY() + angleAroundPlayer;
    float offsetX = dx * sin( glm::radians(theta) );
    float offsetZ = dx * cos( glm::radians(theta) );

    position.x = player->getPosition().x - offsetX;
    position.z = player->getPosition().z - offsetZ;
    position.y = player->getPosition().y + dy;
}
