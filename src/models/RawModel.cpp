//
// Created by kkeiper on 4/23/2022.
//

#include "RawModel.h"

RawModel::RawModel(unsigned int vao, unsigned int vertexCount) : vao(vao), vertexCount(vertexCount) {

}

unsigned int RawModel::getVao() const {
    return vao;
}

unsigned int RawModel::getVertexCount() const {
    return vertexCount;
}
