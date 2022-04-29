//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_CAMERA_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_CAMERA_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Player.h"

class Camera {
protected:
    PlayerPtr player = nullptr;
    float distanceFromPlayer = 80;
    float angleAroundPlayer = 0;

    glm::vec3 position = glm::vec3(0, 0, 0);

    // rotation on x
    float pitch = 30.f;

    // rotation on y
    float yaw = 0.f;

    // rotation on z
    float roll = 0.f;

protected:
    void calculateZoom(const SDL_Event *e);
    void calculatePitch(const SDL_Event *e);
    void calculateAngleAroundPlayer(const SDL_Event *e);

    float calculateHorizontalDistance();
    float calculateVerticalDistance();
    void calculateCameraPosition(float dx, float dy);

public:
    explicit Camera(const PlayerPtr& player);
    explicit Camera(const glm::vec3& position);

    const glm::vec3 &getPosition() const;

    float getPitch() const;
    float getYaw() const;
    float getRoll() const;

    void move();

    void input(const SDL_Event* e);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_CAMERA_H
