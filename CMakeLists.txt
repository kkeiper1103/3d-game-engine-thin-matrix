cmake_minimum_required(VERSION 3.21)
project(3d_game_engine_thin_matrix)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(game3d
        main.cpp
        vendor/glad/src/glad.c


        src/renderEngine/DisplayManager.cpp src/renderEngine/DisplayManager.h src/models/RawModel.cpp
        src/models/RawModel.h src/renderEngine/Loader.cpp src/renderEngine/Loader.h src/renderEngine/Renderer.cpp
        src/renderEngine/Renderer.h src/shaders/ShaderProgram.cpp src/shaders/ShaderProgram.h
        src/shaders/StaticShader.cpp src/shaders/StaticShader.h src/textures/ModelTexture.cpp
        src/textures/ModelTexture.h src/models/TexturedModel.cpp src/models/TexturedModel.h
        src/shaders/Shader.cpp)

target_include_directories(game3d PRIVATE vendor/SDL2-win/include)
target_include_directories(game3d PRIVATE vendor/glad/include)
target_include_directories(game3d PRIVATE vendor)

target_link_directories(game3d PRIVATE vendor/SDL2-win/lib)

target_link_libraries(game3d PRIVATE OpenGL32 SDL2 SDL2main)