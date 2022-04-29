//
// Created by kkeiper on 4/28/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_PLAYER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_PLAYER_H


#include "Entity.h"
#include "terrains/Terrain.h"

#include <SDL2/SDL.h>

class Player : public Entity {
protected:
    static constexpr float RUN_SPEED = 20;
    static constexpr float TURN_SPEED = 160;
    static constexpr float GRAVITY = -65;
    static constexpr float JUMP_POWER = 30;

    static constexpr float TERRAIN_HEIGHT = 0;

    bool onGround = true;

    float currentSpeed = 0;
    float currentTurnSpeed = 0;
    float upwardSpeed = 0;

protected:
    void checkInputs();
    void jump();

public:
    Player(const TexturedModel& model, const glm::vec3& position);

    void move(const TerrainPtr& terrainPtr);
};
typedef std::shared_ptr<Player> PlayerPtr;

#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_PLAYER_H
