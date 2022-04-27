//
// Created by kkeiper1103 on 4/27/22.
//

#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(const TerrainTexture &backgroundTexture, const TerrainTexture &rTexture,
                                       const TerrainTexture &gTexture, const TerrainTexture &bTexture)
        : backgroundTexture(backgroundTexture), rTexture(rTexture), gTexture(gTexture), bTexture(bTexture) {}

const TerrainTexture &TerrainTexturePack::getBackgroundTexture() const {
    return backgroundTexture;
}

const TerrainTexture &TerrainTexturePack::getRTexture() const {
    return rTexture;
}

const TerrainTexture &TerrainTexturePack::getGTexture() const {
    return gTexture;
}

const TerrainTexture &TerrainTexturePack::getBTexture() const {
    return bTexture;
}
