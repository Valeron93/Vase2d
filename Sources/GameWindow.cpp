#include "GameWindow.h"

void GameWindow::init() {

    SDL::GL::SetSwapInterval(1);
    RenderAPI::SetClearColor();

    mCamera = MakeUnique<OrthographicCamera>(mWindowWidth, mWindowHeight);
    mRenderer = MakeUnique<BatchRenderer>();

    onWindowResized(mWindowWidth, mWindowHeight);
}

void GameWindow::render(float deltaTime) {

    static float time = 0.0f;
    time += deltaTime;

    char fps[20];
    sprintf(fps, "%i", int(1.0f / deltaTime));

    SDL_SetWindowTitle(window, fps);

    mRenderer->render(Vec2(-0.5f, 0), Vec4(0.7f, 0.5f, 0.2f, 1.0f));
    mRenderer->render(Vec2(0.5f, 0), Vec4(0.2f, 0.4f, 0.9f, 1.0f));

    mRenderer->flush();
}

GameWindow::GameWindow(const char *title) noexcept {

    window = nullptr;
    glContext = nullptr;

    mWindowWidth = 800;
    mWindowHeight = 600;

    SDL::Init();
    window = SDL::CreateWindow(title, mWindowWidth, mWindowHeight);
    glContext = SDL::GL::CreateContext(window);
    GladLoader::Load();

    VASE_LOG_INFO("OpenGL Version: " << glGetString(GL_VERSION));
    VASE_LOG_INFO("OpenGL Vendor: " << glGetString(GL_VENDOR));
    VASE_LOG_INFO("OpenGL Renderer: " << glGetString(GL_RENDERER));
}

GameWindow::~GameWindow() {
    if (window != nullptr) {

        if (glContext != nullptr) {
            SDL::GL::DeleteContext(glContext);
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void GameWindow::onWindowResized(int width, int height) {

    RenderAPI::Viewport(width, height);
    mCamera->setWidthAndHeight(width, height);
    mRenderer->setProjectionMatrix(mCamera->getProjectionMatrix());

}

void GameWindow::onEvent(const SDL::Event& event) {

    switch (event.type) {

        case SDL_WINDOWEVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    this->mWindowWidth = event.window.data1;
                    this->mWindowHeight = event.window.data2;
                    onWindowResized(mWindowWidth, mWindowHeight);
                    break;
            }
            break;
    }
}

void GameWindow::run() {

    init();
    SDL::Event event;

    uint64_t last;
    uint64_t now = SDL_GetPerformanceCounter();

    bool run = true;

    while (run) {

        last = now;
        now = SDL_GetPerformanceCounter();

        auto deltaTime = ((float) ((now - last)) / (float) SDL_GetPerformanceFrequency());

        RenderAPI::Clear();
        render(deltaTime);

        while (SDL::PollEvent(event)) {
            switch (event.type) {
                case SDL_QUIT:
                    run = false;
                    break;

                default:
                    onEvent(event);
            }
        }
        SDL::GL::SwapWindow(window);
    }
}



