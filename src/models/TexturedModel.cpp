//
// Created by kkeiper on 4/24/2022.
//

#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel &model, const ModelTexture &texture) : rawModel(model), texture(texture) {

    // this is for comparing the texturedmodel in a map in MasterRenderer
    id = (model.getVao() << 4) + (texture.getID());
}

const RawModel &TexturedModel::getRawModel() const {
    return rawModel;
}

const ModelTexture &TexturedModel::getTexture() const {
    return texture;
}
