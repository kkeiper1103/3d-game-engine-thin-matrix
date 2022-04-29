//
// Created by kkeiper on 4/25/2022.
//

#include <iostream>
#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader, const TerrainTexturePack &texturePack,
                 const TerrainTexture &blendMap, const std::string& heightmap) :
        x(gridX * SIZE),
        z(gridZ * SIZE),
        model(RawModel(0, 0)), texturePack(texturePack), blendMap(blendMap) {


    model = generateTerrain(loader, heightmap);
}

RawModel Terrain::generateTerrain(Loader &loader, const std::string& heightMap) {

    // load the heightmap into memory with a custom struct
    ImageInfo image(heightMap);

    int VERTEX_COUNT = image.height;
    int count = VERTEX_COUNT * VERTEX_COUNT;

    std::vector<float> vertices(count * 3);
    std::vector<float> normals(count * 3);
    std::vector<float> textureCoords(count * 2);
    std::vector<unsigned int> indices( 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1) );

    int currentVertex = 0;
    for(auto i=0; i < VERTEX_COUNT; i++) {
        for(auto j=0; j < VERTEX_COUNT; j++) {

            vertices[currentVertex*3 + 0] = -(float)j / ((float) VERTEX_COUNT - 1) * SIZE;
            vertices[currentVertex*3 + 1] = getHeight(i, j, image);
            vertices[currentVertex*3 + 2] = -(float)i / ((float) VERTEX_COUNT - 1) * SIZE;

            glm::vec3 normal = calculateNormal(i, j, image);

            normals[currentVertex*3 + 0] = normal.x;
            normals[currentVertex*3 + 1] = normal.y;
            normals[currentVertex*3 + 2] = normal.z;

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

/**
 *
 * @param x
 * @param z
 * @param image
 * @return
 */
float Terrain::getHeight(int x, int z, const ImageInfo& image) {
    if(x < 0 || x >= image.width || z < 0 || z >= image.height) {
        return 0;
    }

    /**
     * using pointer arithmetic to get the specific argb of the requested x,z coordinate
     * x + (height * y) * channels results in going to the correct in-memory location of pixels
     */
    unsigned char* pixelOffset = image.pixels + (x + image.height * z) * image.channels;

    unsigned char r = pixelOffset[0],
        g = pixelOffset[1],
        b = pixelOffset[2],
        a = (image.channels >= 4) ? pixelOffset[3] : 0xff;

    // this is to mimic the BufferedImage.getRGB() method
    // stores an argb value in the format of 0xAARRGGBB, so A is 24 bits to the left, R is 16 bits to the left, G is 8 bits to the left, and B is normal.
    int rgb = (a << 24) + (r << 16) + (g << 8) + (b);

    auto h = (float) rgb;

    // this shifts the y value up by half its range
    h += MAX_PIXEL_COLOR / 2.f;

    // this dampens the y value by half its range
    h /= MAX_PIXEL_COLOR / 2.f;

    // this scales it by the max height so we end up with a value between -40 and 40
    h *= MAX_HEIGHT;

    return h;
}

/**
 * Cheap way to calculate normal when we know what the various neighboring heights are
 *
 * @param x
 * @param z
 * @param image
 * @return
 */
glm::vec3 Terrain::calculateNormal(int x, int z, const ImageInfo& image) {

    float heightL = getHeight(x-1, z, image);
    float heightR = getHeight(x+1, z, image);
    float heightD = getHeight(x, z-1, image);
    float heightU = getHeight(x, z+1, image);

    glm::vec3 normal(heightL - heightR, 2.f, heightD - heightU);
    normal = glm::normalize(normal);

    return normal;
}
