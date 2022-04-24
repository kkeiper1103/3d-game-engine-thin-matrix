//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H


#include "ShaderProgram.h"

class StaticShader : public ShaderProgram {
protected:
    static std::string vertexFile;
    static std::string fragmentFile;

    int location_transformationMatrix;

    void bindAttributes() override;
    void getAllUniformLocations() override;

public:
    StaticShader();

    void loadTransformationMatrix(const glm::mat4& matrix);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_STATICSHADER_H
