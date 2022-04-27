//
// Created by kkeiper on 4/24/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_MODELTEXTURE_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_MODELTEXTURE_H


class ModelTexture {
protected:
    unsigned int textureID;

    float shineDamper = 1.f;
    float reflectivity = 0.f;

public:
    explicit ModelTexture(unsigned int id);

    inline unsigned int getID() const {
        return textureID;
    }

    float getShineDamper() const;
    void setShineDamper(float shineDamper);

    float getReflectivity() const;
    void setReflectivity(float reflectivity);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_MODELTEXTURE_H
