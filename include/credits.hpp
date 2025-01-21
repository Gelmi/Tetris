#ifndef CREDITS_HPP
#define CREDITS_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "view.hpp"

class Credits : public View {
public:
    Credits(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) 
        : View(sharedWindow, sharedRenderer) {};
    ~Credits();

    void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer);
    void ShowCredits();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screen{nullptr};
    TTF_Font* font;
};

#endif
