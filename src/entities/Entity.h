//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_ENTITY_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_ENTITY_H

#include <memory>

#include <glm/glm.hpp>

#include "models/TexturedModel.h"

class Entity {
protected:
    TexturedModel model;

    glm::vec3 position;
    float rotX, rotY, rotZ;
    float scale;

public:
    Entity(const TexturedModel& model, const glm::vec3& position, float rx, float ry, float rz, float scale);
    virtual ~Entity() = default;

    void increasePosition(float dx, float dy, float dz);
    void increaseRotation(float rx, float ry, float rz);

public:
    const TexturedModel &getModel() const {
        return model;
    }

    void setModel(const TexturedModel &model) {
        Entity::model = model;
    }

    const glm::vec3 &getPosition() const {
        return position;
    }

    void setPosition(const glm::vec3 &position) {
        Entity::position = position;
    }

    float getRotX() const {
        return rotX;
    }

    void setRotX(float rotX) {
        Entity::rotX = rotX;
    }

    float getRotY() const {
        return rotY;
    }

    void setRotY(float rotY) {
        Entity::rotY = rotY;
    }

    float getRotZ() const {
        return rotZ;
    }

    void setRotZ(float rotZ) {
        Entity::rotZ = rotZ;
    }

    float getScale() const {
        return scale;
    }

    void setScale(float scale) {
        Entity::scale = scale;
    }
};

typedef std::shared_ptr<Entity> EntityPtr;


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_ENTITY_H
