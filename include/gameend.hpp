#ifndef GAMEEND_HPP
#define GAMEEND_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "view.hpp"
#include <string>

class GameEnd : public View {
public:

    GameEnd(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer)
        : View(sharedWindow, sharedRenderer) {
            this->text = "You lose!";
        };  
    GameEnd(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer, std::string text) :
        GameEnd(sharedWindow, sharedRenderer) {
            this->text = text; 
        };

    void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer);
    void changeText(std::string text);
    int showgameend();

    // Menu() = default;
private:
    int close{0};
    SDL_Window* window{nullptr};
    // SDL_Surface* screen{nullptr};
    SDL_Renderer* renderer{nullptr};
    TTF_Font * font;
    std::string text;
};

#endif
