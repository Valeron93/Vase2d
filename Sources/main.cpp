#include "GameWindow.h"

int main()
{
    auto window = std::make_unique<GameWindow>("Game");
    window->run();
    return 0;
}