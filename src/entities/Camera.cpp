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

}

Camera::Camera(const glm::vec3 &position) : position(position) {

}
