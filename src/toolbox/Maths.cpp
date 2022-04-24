//
// Created by kkeiper on 4/24/2022.
//

#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(const glm::vec3 &translation, float rx, float ry, float rz, float scale) {
    glm::mat4 model(1.f);

    model = glm::translate(model, translation);

    model = glm::rotate(model, glm::radians(rx), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(ry), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rz), glm::vec3(0, 0, 1));

    model = glm::scale(model, glm::vec3(scale, scale, scale));

    return model;
}
