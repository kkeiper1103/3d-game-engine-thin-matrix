//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_OBJLOADER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_OBJLOADER_H

#include <vector>
#include <string>
#include <sstream>

#include <glm/glm.hpp>

#include "models/RawModel.h"
#include "Loader.h"

class OBJLoader {
private:
    static std::vector<std::string> split(const std::string& line, const char delimiter = ' ');
    static void processVertex(const std::vector<std::string>& parts, std::vector<unsigned int>& indices,
                              std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& textureArray, std::vector<float>& normalsArray);

public:
    static RawModel loadObjModel(const std::string& fileName, Loader& loader);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_OBJLOADER_H
