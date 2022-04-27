//
// Created by kkeiper1103 on 4/27/22.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINTEXTUREPACK_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINTEXTUREPACK_H


#include "TerrainTexture.h"

class TerrainTexturePack {
protected:
    TerrainTexture backgroundTexture;
    TerrainTexture rTexture;
    TerrainTexture gTexture;
    TerrainTexture bTexture;

public:
    TerrainTexturePack(const TerrainTexture &backgroundTexture, const TerrainTexture &rTexture,
                       const TerrainTexture &gTexture, const TerrainTexture &bTexture);

    const TerrainTexture &getBackgroundTexture() const;

    const TerrainTexture &getRTexture() const;

    const TerrainTexture &getGTexture() const;

    const TerrainTexture &getBTexture() const;
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAINTEXTUREPACK_H
