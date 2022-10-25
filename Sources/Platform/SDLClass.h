#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <Core/Logging.h>

namespace SDL {
    using Event = SDL_Event;
    using Window = SDL_Window;

    void Init();
    Window *CreateWindow(const char *title, int width, int height);
    bool PollEvent(Event &event);
    inline void Quit();

    namespace GL {
        using Context = SDL_GLContext;

        Context CreateContext(Window *window);

        void DeleteContext(Context context);

        void SwapWindow(Window *window);

        void SetSwapInterval(int interval);

    }

}