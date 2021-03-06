//
// Created by kkeiper on 4/25/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAIN_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAIN_H

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>

#include "textures/ModelTexture.h"
#include "models/RawModel.h"
#include "renderEngine/Loader.h"
#include "textures/TerrainTexturePack.h"

/**
 * This wraps some fields that are expected to be always be passed
 * includes height, width and bpp of image, as well as the raw pixels
 * RAII cleanup of pixels, so don't call stbi_image_free()
 */
struct ImageInfo {
    int width, height, channels;
    unsigned char* pixels = nullptr;

    explicit ImageInfo(const std::string& filename) {
        pixels = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if(!pixels) {
            std::cerr << "Something went wrong loading " << filename << std::endl;
            width = 0; height = 0; channels = 0; pixels = nullptr;
        }
    }

    /**
     * When the ImageInfo goes out of scope, free the pixels
     */
    ~ImageInfo() {
        stbi_image_free(pixels);
    }

    /**
     *
     * @param x
     * @param y
     * @return
     */
    int getPixel(int x, int y) {
        if(x < 0 || x >= width || y < 0 || y >= height) return 0;

        unsigned char* pixelOffset = pixels + (x + height * y) * channels;

        unsigned char r = pixelOffset[0],
                g = pixelOffset[1],
                b = pixelOffset[2],
                a = (channels >= 4) ? pixelOffset[3] : 0xff;

        // this is to mimic the BufferedImage.getRGB() method
        // stores an argb value in the format of 0xAARRGGBB, so A is 24 bits to the left, R is 16 bits to the left, G is 8 bits to the left, and B is normal.
        return (a << 24) + (r << 16) + (g << 8) + (b);
    }
};

class Terrain {
protected:
    constexpr static const float SIZE = 800;
    constexpr static const float MAX_HEIGHT = 40;
    constexpr static const float MAX_PIXEL_COLOR = 256 * 256 * 256;

    float x=0, z=0;

    std::vector<std::vector<float>> heights;

    RawModel model;
    TerrainTexturePack texturePack;

    TerrainTexture blendMap;


    float getHeight(int x, int z, const ImageInfo& image);
    glm::vec3 calculateNormal(int x, int z, const ImageInfo& image);

public:
    Terrain(int gridX, int gridZ, Loader& loader, const TerrainTexturePack& texturePack, const TerrainTexture& blendMap, const std::string& heightmap);

    RawModel generateTerrain(Loader& loader, const std::string& heightMap);

    float getX() const;
    float getZ() const;

    const RawModel &getModel() const;

    const TerrainTexturePack &getTexturePack() const;

    const TerrainTexture &getBlendMap() const;

    float getHeightOfTerrain(float worldX, float worldY);
};
typedef std::shared_ptr<Terrain> TerrainPtr;

#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TERRAIN_H
