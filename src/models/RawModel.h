//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_RAWMODEL_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_RAWMODEL_H


class RawModel {
protected:
    unsigned int vao;
    unsigned int vertexCount;

public:
    RawModel(unsigned int vao, unsigned int vertexCount);

    unsigned int getVao() const;
    unsigned int getVertexCount() const;
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_RAWMODEL_H
