cmake_minimum_required (VERSION 3.15.0)

project(Rendering LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_executable(Rendering)


target_sources(Rendering 
PRIVATE
    Src/main.cpp
    Dependencies/tinyrenderer/tgaimage.cpp
)

target_include_directories(Rendering 
PRIVATE
    Dependencies/tinyrenderer
    Src
)
