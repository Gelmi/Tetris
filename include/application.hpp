#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>

class Application {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Application();
    ~Application();

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;
};

#endif
