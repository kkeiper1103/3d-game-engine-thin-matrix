# 3d-game-engine-thin-matrix

This is a C++ translation of the [3D Game Engine Series by ThinMatrix](https://www.youtube.com/watch?v=VS8wlS9hF8E&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP) on Youtube.

Original language is Java / LWJGL. This uses SDL2 for windowing / event system, Glad for GL Loading, and stb for image pixel data. Built with CMake in CLion, although any IDE with cmake support (or even just raw cmake) should suffice.

Currently built against Windows, but some minimal cmake customization will make it compile on other platforms. The C++ code is written with cross platform in mind, so it's just the cmakelists.txt file that needs adapted.
