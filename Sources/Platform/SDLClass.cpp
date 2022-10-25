#include "SDLClass.h"

void SDL::Init() {

    VASE_LOG_INFO("Initializing SDL");

    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        VASE_LOG_ERROR("Failed to initalize SDL: " << SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
}

SDL::Window *SDL::CreateWindow(const char *title, int width, int height) {

    Window *window = SDL_CreateWindow(title,
                                      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      width, height,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {

        VASE_LOG_ERROR("Failed to create SDL window!\n");
        exit(1);
    }

    return window;

}

bool SDL::PollEvent(SDL::Event &event) {
    return SDL_PollEvent(&event);
}

void SDL::Quit() {
    SDL_Quit();
}

SDL::GL::Context SDL::GL::CreateContext(SDL::Window *window) {
    GL::Context glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr) {
        VASE_LOG_ERROR("Failed to create GL context: " << SDL_GetError());
        exit(1);
    }

    return glContext;
}

void SDL::GL::DeleteContext(SDL::GL::Context context) {
    SDL_GL_DeleteContext(context);
}

void SDL::GL::SwapWindow(SDL::Window *window) {
    SDL_GL_SwapWindow(window);
}

void SDL::GL::SetSwapInterval(int interval) {
    SDL_GL_SetSwapInterval(interval);
}
