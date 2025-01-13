#include "application.hpp"
#include <iostream>

Application::Application() : window(nullptr), renderer(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating window (Application): " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

Application::~Application() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Application::GetWindow() const {
    return window;
}

SDL_Renderer* Application::GetRenderer() const {
    return renderer;
}
