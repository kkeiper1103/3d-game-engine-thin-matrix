//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_CAMERA_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_CAMERA_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Camera {
protected:
    glm::vec3 position = glm::vec3(0, 0, 0);

    float pitch = 0.f;
    float yaw = 0.f;
    float roll = 0.f;

public:
    Camera();
    explicit Camera(const glm::vec3& position);

    const glm::vec3 &getPosition() const;

    float getPitch() const;

    float getYaw() const;

    float getRoll() const;

    void move();
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_CAMERA_H
