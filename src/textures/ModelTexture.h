//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_MODELTEXTURE_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_MODELTEXTURE_H


class ModelTexture {
protected:
    unsigned int textureID;

public:
    explicit ModelTexture(unsigned int id);


    inline unsigned int getID() const {
        return textureID;
    }
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_MODELTEXTURE_H
