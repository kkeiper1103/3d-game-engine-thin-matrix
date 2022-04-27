//
// Created by kkeiper1103 on 4/27/22.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINTEXTURE_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINTEXTURE_H


class TerrainTexture {
protected:
    unsigned int id;

public:
    explicit TerrainTexture(unsigned int id);

    unsigned int getId() const;
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINTEXTURE_H
