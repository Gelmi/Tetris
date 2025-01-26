#ifndef MULTIGAMEVIEW_HPP
#define MULTIGAMEVIEW_HPP

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gamedata.hpp"
#include "gameview.hpp"

class MultiGameView : public GameView {
    public:
        MultiGameView(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer)
            : GameView(sharedWindow, sharedRenderer) {
                font = TTF_OpenFont("./assets/stocky.ttf", 36);
                if (!font) {
                    std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
                    exit(1);
                }
            };
        ~MultiGameView();
        void Draw(GameData data);
        void DrawWaitConnection();
        void DrawWaitStart();
        void DrawResults(GameData data);

    private:
        TTF_Font* font;
        
};

#endif
