//
// Created by kkeiper on 4/23/2022.
//

#ifndef INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H
#define INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H

#include <glad/glad.h>
#include "models/RawModel.h"
#include "models/TexturedModel.h"

class Renderer {
public:
    void prepare();
    void render(const TexturedModel& texturedModel);
};


#endif //INC_3D_GAME_ENGINE_THIN_MATRIX_RENDERER_H
