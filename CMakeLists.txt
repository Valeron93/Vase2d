cmake_minimum_required(VERSION 3.10)
project(Vase2d)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/Output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB VASE2D_SOURCES_INPUT
        Sources/Input/Input.cpp)

file(GLOB VASE2D_SOURCES_PLATFORM
        Sources/Platform/RenderAPI.cpp
        Sources/Platform/SDLClass.cpp)

file(GLOB VASE2D_SOURCES_RENDERER
        Sources/Renderer/BatchRenderer.cpp
        Sources/Renderer/Shader.cpp
        Sources/Renderer/Camera/OrthographicCamera.cpp)

file(GLOB VASE2D_SOURCES_ROOT
        Sources/GameWindow.cpp
        Sources/main.cpp)

include_directories(Sources)

add_executable(Vase2d
        ${VASE2D_SOURCES_ROOT}
        ${VASE2D_SOURCES_PLATFORM}
        ${VASE2D_SOURCES_RENDERER}
        ${VASE2D_SOURCES_INPUT})

find_package(OpenGL REQUIRED)

set(GLAD_DIRS Dependencies/glad)

set(SDL_SHARED ON)
set(SDL_STATIC OFF)

add_subdirectory(Dependencies/SDL2)
add_subdirectory(Dependencies/glm)

target_include_directories(Vase2d PRIVATE Dependencies/SDL2/include)

add_library(glad "${GLAD_DIRS}/include/glad/glad.h" "${GLAD_DIRS}/src/glad.c")
target_include_directories(glad PUBLIC ${GLAD_DIRS}/include)

target_link_libraries(Vase2d OpenGL::GL)
target_link_libraries(Vase2d glad glm)
target_link_libraries(Vase2d SDL2)
