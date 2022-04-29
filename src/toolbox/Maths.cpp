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

glm::mat4 Maths::createViewMatrix(const Camera &camera) {
    glm::mat4 view(1.0);

    view = glm::rotate(view, glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
    view = glm::rotate(view, glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));
    view = glm::rotate(view, glm::radians(camera.getRoll()), glm::vec3(0, 0, 1));

    view = glm::translate(view, (camera.getPosition() * -1.f));

    return view;
}

float Maths::barryCentric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &position) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x)  * (p1.z - p3.z);

    float l1 = ((p2.z - p3.z) * (position.x - p3.x) + (p3.x - p2.x) * (position.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (position.x - p3.x) + (p1.x - p3.x) * (position.y - p3.z)) / det;
    float l3 = 1.f - l1 - l2;

    return l1 * p1.y + l2* p2.y + l3 * p3.y;
}
