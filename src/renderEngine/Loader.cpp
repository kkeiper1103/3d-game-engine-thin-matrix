//
// Created by kkeiper on 4/23/2022.
//

#define STB_IMAGE_IMPLEMENTATION
#include "Loader.h"

unsigned int Loader::createVAO() {
    unsigned int vaoID;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    vaos.push_back(vaoID);

    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::vector<float> &data) {
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    vbos.push_back(vbo);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

RawModel Loader::loadToVAO(const std::vector<float> &positions, const std::vector<float>& texCoords,
                           const std::vector<float>& normals, const std::vector<unsigned int>& indices) {
    unsigned int vaoID = createVAO();

    bindIndicesBuffer(indices);

    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, texCoords);
    storeDataInAttributeList(2, 3, normals);

    unbindVAO();

    return RawModel(vaoID, indices.size());
}

void Loader::cleanUp() {
    glDeleteVertexArrays(vaos.size(), &vaos[0]);
    glDeleteBuffers(vbos.size(), &vbos[0]);
    glDeleteTextures(textures.size(), &textures[0]);
}

void Loader::bindIndicesBuffer(const std::vector<unsigned int> &indices) {
    unsigned int vboId;
    glGenBuffers(1, &vboId);
    vbos.push_back(vboId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

unsigned int Loader::loadTexture(const std::string &fileName) {

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    stbi_set_flip_vertically_on_load(true);

    int w, h, channels;
    unsigned char* pixels = stbi_load(fileName.c_str(), &w, &h, &channels, STBI_rgb_alpha);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -.4f);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // not generating mipmaps makes a black screen? what?
    // possibly because the GL_TEXTURE_MIN_FILTER parameter? maybe it sees that I'm specifying a minification filter, so it's waiting for
    // the mipmap to be generated?
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    textures.push_back(textureId);

    return textureId;
}
