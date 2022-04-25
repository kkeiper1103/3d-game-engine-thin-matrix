//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_LOADER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_LOADER_H

#include <vector>
#include <string>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "models/RawModel.h"


class Loader {
protected:
    std::vector<unsigned int> vaos;
    std::vector<unsigned int> vbos;
    std::vector<unsigned int> textures;

protected:
    unsigned int createVAO();
    void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float>& data);
    void unbindVAO();

    void bindIndicesBuffer(const std::vector<unsigned int>& indices);

public:
    RawModel loadToVAO(const std::vector<float>& positions, const std::vector<float>& texCoords,
                       const std::vector<float>& normals, const std::vector<unsigned int>& indices);

    unsigned int loadTexture(const std::string& fileName);

    void cleanUp();
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_LOADER_H
