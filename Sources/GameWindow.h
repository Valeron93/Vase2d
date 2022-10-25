#pragma once

#include <Platform/RenderAPI.h>
#include <Renderer/BatchRenderer.h>
#include <Renderer/Camera/OrthographicCamera.h>

#include <Platform/SDLClass.h>
#include <Platform/GladLoader.h>

class GameWindow {

private:
    SDL_Window *window;
    SDL_GLContext glContext;

protected:
    Unique<OrthographicCamera> mCamera;
    Unique <BatchRenderer> mRenderer;

private:
    int mWindowWidth;
    int mWindowHeight;

public:
    explicit GameWindow(const char *title) noexcept;
    ~GameWindow();
    void run();

private:
    void init();
    void render(float deltaTime);
    void onWindowResized(int width, int height);
    void onEvent(const SDL::Event& event);

};



