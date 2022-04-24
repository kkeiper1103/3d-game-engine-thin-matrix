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

public:
    TexturedModel(const RawModel& model, const ModelTexture& texture);


    const RawModel &getRawModel() const;
    const ModelTexture &getTexture() const;
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_TEXTUREDMODEL_H
