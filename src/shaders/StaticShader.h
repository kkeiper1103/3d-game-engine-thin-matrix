//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H


#include "ShaderProgram.h"
#include "entities/Camera.h"
#include "entities/Light.h"

class StaticShader : public ShaderProgram {
protected:
    static std::string vertexFile;
    static std::string fragmentFile;

    int location_transformationMatrix;
    int location_projectionMatrix;
    int location_viewMatrix;
    int location_lightPosition;
    int location_lightColor;
    int location_shineDamper;
    int location_reflectivity;
    int location_fakeLighting;

    void bindAttributes() override;
    void getAllUniformLocations() override;

public:
    StaticShader();

    void loadTransformationMatrix(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& matrix);
    void loadViewMatrix(const Camera& camera);

    void loadLight(const Light& light);

    void loadShineVariables(float damper, float reflectivity);

    void loadFakeLighting(bool fakeLighting);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H
