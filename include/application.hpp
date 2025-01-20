#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>
#include "view.hpp"

class Application {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    // Application(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) : View(sharedWindow, sharedRenderer) {};
    Application();
    ~Application();
    void Run();

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;
};

#endif
