//
// Created by kkeiper on 4/24/2022.
//

#include "Entity.h"

Entity::Entity(const TexturedModel &model, const glm::vec3 &position, float rx, float ry, float rz, float scale) :
model(model), position(position), rotX(rx), rotY(ry), rotZ(rz), scale(scale) {

}

void Entity::increasePosition(float dx, float dy, float dz) {
    position.x += dx;
    position.y += dy;
    position.z += dz;
}

void Entity::increaseRotation(float rx, float ry, float rz) {
    rotX += rx;
    rotY += ry;
    rotZ += rz;
}
