#ifndef MENU_HPP
#define MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "view.hpp"

class Menu : public View {
public:

    Menu(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer)
        : View(sharedWindow, sharedRenderer) {}
    ~Menu();
    void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer);
    int showmenu();

private:
    int close{0};
    SDL_Window* window{nullptr};
    SDL_Surface* screen{nullptr};
    SDL_Renderer* renderer{nullptr};
    TTF_Font * font;
    TTF_Font * fontTitle;
};

#endif
