//
// Created by kkeiper on 4/25/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_LIGHT_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_LIGHT_H

#include <glm/glm.hpp>

class Light {
protected:
    glm::vec3 position;
    glm::vec3 color;

public:
    Light(const glm::vec3 &position, const glm::vec3 &color);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_LIGHT_H
