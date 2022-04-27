//
// Created by kkeiper on 4/25/2022.
//

#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader, const TerrainTexturePack &texturePack,
                 const TerrainTexture &blendMap) :
        x(gridX * SIZE),
        z(gridZ * SIZE),
        model(RawModel(0, 0)), texturePack(texturePack), blendMap(blendMap) {


    model = generateTerrain(loader);
}

RawModel Terrain::generateTerrain(Loader &loader) {
    int count = VERTEX_COUNT * VERTEX_COUNT;

    std::vector<float> vertices(count * 3);
    std::vector<float> normals(count * 3);
    std::vector<float> textureCoords(count * 2);
    std::vector<unsigned int> indices( 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1) );

    int currentVertex = 0;
    for(auto i=0; i < VERTEX_COUNT; i++) {
        for(auto j=0; j < VERTEX_COUNT; j++) {

            vertices[currentVertex*3 + 0] = -(float)j / ((float) VERTEX_COUNT - 1) * SIZE;
            vertices[currentVertex*3 + 1] = 0;
            vertices[currentVertex*3 + 2] = -(float)i / ((float) VERTEX_COUNT - 1) * SIZE;

            normals[currentVertex*3 + 0] = 0;
            normals[currentVertex*3 + 1] = 1;
            normals[currentVertex*3 + 2] = 0;

            textureCoords[currentVertex*2 + 0] = (float)j / ((float) VERTEX_COUNT - 1);
            textureCoords[currentVertex*2 + 1] = (float)i / ((float) VERTEX_COUNT - 1);

            currentVertex++;
        }
    }

    int index = 0;
    for(auto gz=0; gz < VERTEX_COUNT - 1; gz++) {
        for(auto gx=0; gx < VERTEX_COUNT - 1; gx++) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;

            indices[index++] = topLeft;
            indices[index++] = bottomLeft;
            indices[index++] = topRight;
            indices[index++] = topRight;
            indices[index++] = bottomLeft;
            indices[index++] = bottomRight;
        }
    }

    return loader.loadToVAO(vertices, textureCoords, normals, indices);
}

float Terrain::getX() const {
    return x;
}

float Terrain::getZ() const {
    return z;
}

const RawModel &Terrain::getModel() const {
    return model;
}

const TerrainTexturePack &Terrain::getTexturePack() const {
    return texturePack;
}

const TerrainTexture &Terrain::getBlendMap() const {
    return blendMap;
}
