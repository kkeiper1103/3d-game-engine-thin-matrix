//
// Created by kkeiper on 4/24/2022.
//

#include "OBJLoader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <iterator>

RawModel OBJLoader::loadObjModel(const std::string &fileName, Loader &loader) {

    std::fstream file(fileName);
    if(!file.is_open()) {
        fprintf(stderr, "Unable to Open File: %s\n", fileName.c_str());
        return RawModel(0, 0);
    }

    std::string line;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    // not sure about these...
    std::vector<float> textureData;
    std::vector<float> normalData;

    /**
     *
     */
    while(!file.eof()) {
        std::getline(file, line);

        // this tokenizes the line into a vector delimited by spaces
        std::vector<std::string> parts = split(line, ' ');

        // starts with "v "
        if( line.find("v ") == 0 ) {

            // emplace_back constructs a stored-item using the args as the constructor parameters
            // nearly equivalent to .push_back( std::move(glm::vec3(part1, part2, part3)) );
            vertices.emplace_back( std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3]) );
        }
        else if( line.find("vn ") == 0) {
            normals.emplace_back( std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3]) );
        }
        else if(line.find("vt ") == 0) {
            textures.emplace_back( std::stof(parts[1]), std::stof(parts[2]) );
        }
        else if(line.find("f ") == 0) {
            // this should only be empty on the first face element that we find
            if( normalData.empty() || textureData.empty() ) {
                textureData.resize(vertices.size() * 2);
                normalData.resize(vertices.size() * 3);
            }


            auto tri1 = split(parts[1], '/'),
                tri2 = split(parts[2], '/'),
                tri3 = split(parts[3], '/');

            processVertex( tri1, indices, textures, normals, textureData, normalData );
            processVertex( tri2, indices, textures, normals, textureData, normalData );
            processVertex( tri3, indices, textures, normals, textureData, normalData );
        }
    }

    file.close();

    std::vector<float> verticesData(vertices.size() * 3);

    int currentVertex = 0;
    for(auto& v: vertices) {
        verticesData[currentVertex++] = v.x;
        verticesData[currentVertex++] = v.y;
        verticesData[currentVertex++] = v.z;
    }

    return loader.loadToVAO(verticesData, textureData, indices);
}

std::vector<std::string> OBJLoader::split(const std::string &line, const char delimiter) {
    using namespace std;

    string tmp;
    stringstream ss(line);
    vector<string> parts;

    while(getline(ss, tmp, delimiter)){
        if(!tmp.empty()) parts.push_back(tmp);
    }

    return parts;
}

void OBJLoader::processVertex(const std::vector<std::string>& parts, std::vector<unsigned int> &indices,
                              std::vector<glm::vec2> &textures, std::vector<glm::vec3> &normals,
                              std::vector<float>& textureArray, std::vector<float>& normalsArray) {

    int vertexIndex = std::stoi( parts[0] ) - 1;
    indices.push_back(vertexIndex);

    glm::vec2 currentTex = textures[ std::stoi(parts[1]) - 1 ];
    textureArray[vertexIndex * 2] = currentTex.x;
    textureArray[vertexIndex * 2 + 1] = currentTex.y;

    glm::vec3 currentNormal = normals[ std::stoi(parts[2]) - 1 ];
    normalsArray[vertexIndex * 3] = currentNormal.x;
    normalsArray[vertexIndex * 3 + 1] = currentNormal.x;
    normalsArray[vertexIndex * 3 + 2] = currentNormal.y;

}
