//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_TEXTUREDMODEL_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_TEXTUREDMODEL_H


#include "RawModel.h"
#include "textures/ModelTexture.h"

class TexturedModel {
private:
    RawModel rawModel;
    ModelTexture texture;

    // this specifically is to make this class usable as a map key
    // a std::map is a BST and needs some form of ID to compare against
    // in this situation, we're taking the vao bitshifted left 4 + the texture Id
    unsigned int id;

public:
    TexturedModel(const RawModel& model, const ModelTexture& texture);


    const RawModel &getRawModel() const;
    const ModelTexture &getTexture() const;


    bool operator<(const TexturedModel& rhs) const {
        return id < rhs.id;
    }
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TEXTUREDMODEL_H
