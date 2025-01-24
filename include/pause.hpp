#ifndef PAUSE_HPP
#define PAUSE_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "view.hpp"

class Pause : public View {
public:

    Pause(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer)
        : View(sharedWindow, sharedRenderer) {}
    void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer);
    int showpause();

    // Menu() = default;
private:
    int close{0};
    SDL_Window* window{nullptr};
    // SDL_Surface* screen{nullptr};
    SDL_Renderer* renderer{nullptr};
};

#endif
