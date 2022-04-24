//
// Created by kkeiper on 4/24/2022.
//

#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel &model, const ModelTexture &texture) : rawModel(model), texture(texture) {

}

const RawModel &TexturedModel::getRawModel() const {
    return rawModel;
}

const ModelTexture &TexturedModel::getTexture() const {
    return texture;
}
