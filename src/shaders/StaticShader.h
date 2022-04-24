//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H


#include "ShaderProgram.h"
#include "entities/Camera.h"

class StaticShader : public ShaderProgram {
protected:
    static std::string vertexFile;
    static std::string fragmentFile;

    int location_transformationMatrix;
    int location_projectionMatrix;
    int location_viewMatrix;

    void bindAttributes() override;
    void getAllUniformLocations() override;

public:
    StaticShader();

    void loadTransformationMatrix(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& matrix);
    void loadViewMatrix(const Camera& camera);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H
