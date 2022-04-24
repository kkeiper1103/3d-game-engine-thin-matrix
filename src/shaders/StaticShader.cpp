//
// Created by kkeiper on 4/23/2022.
//

#include "StaticShader.h"

std::string StaticShader::vertexFile = "assets/shaders/vertex.glsl";
std::string StaticShader::fragmentFile = "assets/shaders/fragment.glsl";

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}

StaticShader::StaticShader() : ShaderProgram(vertexFile, fragmentFile) {

}
