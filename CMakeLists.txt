cmake_minimum_required(VERSION 3.21)
project(3d_game_engine_thin_matrix)

set(CMAKE_CXX_STANDARD 20)

# this is needed on windows to statically link the std library into the application
# otherwise, you'll get a missing libgcc_seh_c.dll sort of error when you run the application outside
# of the IDE.
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")


include_directories(src)

add_executable(game3d
        main.cpp
        vendor/glad/src/glad.c


        src/renderEngine/DisplayManager.cpp  src/models/RawModel.cpp
         src/renderEngine/Loader.cpp src/renderEngine/EntityRenderer.cpp
         src/shaders/ShaderProgram.cpp 
        src/shaders/StaticShader.cpp  src/textures/ModelTexture.cpp
         src/models/TexturedModel.cpp src/toolbox/Maths.cpp src/toolbox/Maths.h src/entities/Entity.cpp src/entities/Entity.h src/entities/Camera.cpp src/entities/Camera.h src/renderEngine/OBJLoader.cpp src/renderEngine/OBJLoader.h src/entities/Light.cpp src/entities/Light.h src/renderEngine/MasterRenderer.cpp src/renderEngine/MasterRenderer.h src/terrains/Terrain.cpp src/terrains/Terrain.h src/shaders/TerrainShader.cpp src/shaders/TerrainShader.h src/renderEngine/TerrainRenderer.cpp src/renderEngine/TerrainRenderer.h)

target_include_directories(game3d PRIVATE vendor/glad/include)
target_include_directories(game3d PRIVATE vendor)

find_package(OpenGL REQUIRED)

if(WIN32)
target_include_directories(game3d PRIVATE vendor/SDL2-win/include)
target_link_directories(game3d PRIVATE vendor/SDL2-win/lib)
endif(WIN32)


target_link_libraries(game3d PRIVATE OpenGL::GL SDL2 SDL2main ${CMAKE_DL_LIBS})