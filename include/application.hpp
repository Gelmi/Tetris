#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>

class Application {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;

public:
    // Application(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) : View(sharedWindow, sharedRenderer) {};
    Application();
    ~Application();
    int Run();

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;

    
    int windowWidth = 800;  // Valores padrão iniciais
    int windowHeight = 640; // Valores padrão iniciais
    float scaleX = 1.0f;
    float scaleY = 1.0f;
};

#endif
