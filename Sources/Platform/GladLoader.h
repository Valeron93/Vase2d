#pragma once
#include <glad/glad.h>
#include <SDL.h>
#include <Core/Logging.h>

class GladLoader {
public:
    static void Load() {
        if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
            VASE_LOG_ERROR("Failed to initialize the OpenGL context");
            exit(1);
        }
    }

};