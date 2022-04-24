//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_MATHS_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_MATHS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Maths {
public:
    static glm::mat4 createTransformationMatrix(const glm::vec3& translation, float rx, float ry, float rz, float scale);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_MATHS_H
