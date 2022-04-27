//
// Created by kkeiper on 4/24/2022.
//

#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int id) : textureID(id) {

}

float ModelTexture::getShineDamper() const {
    return shineDamper;
}

void ModelTexture::setShineDamper(float shineDamper) {
    this->shineDamper = shineDamper;
}

float ModelTexture::getReflectivity() const {
    return reflectivity;
}

void ModelTexture::setReflectivity(float reflectivity) {
    this->reflectivity = reflectivity;
}
