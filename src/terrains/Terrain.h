//
// Created by kkeiper on 4/25/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAIN_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAIN_H


#include <memory>

#include "textures/ModelTexture.h"
#include "models/RawModel.h"
#include "renderEngine/Loader.h"

class Terrain {
protected:
    constexpr static const float SIZE = 800;
    constexpr static const float VERTEX_COUNT = 128;

    float x, z;

    RawModel model;
    ModelTexture texture;

public:
    Terrain(int gridX, int gridZ, Loader& loader, const ModelTexture& texture);

    RawModel generateTerrain(Loader& loader);

    float getX() const;
    float getZ() const;

    const RawModel &getModel() const;

    const ModelTexture &getTexture() const;
};
typedef std::shared_ptr<Terrain> TerrainPtr;

#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAIN_H
