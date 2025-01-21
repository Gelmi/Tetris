#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "gamedata.hpp"

class GameView {
    private:
        SDL_Renderer * renderer;
        SDL_Window * window;
        SDL_Texture * boardTexture;
        SDL_Texture * boardTileTexture;
        SDL_Texture * tetrominoTexture;
        SDL_Texture * tetrominoTileTexture;
        TTF_Font * font;

        void DrawBoard(GameData data);
        void DrawTetromino(GameData data);
        void DrawStats(GameData data);
        void DrawNextTetromino(GameData data);

    public:
        GameView(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer);
        ~GameView();
        void Draw(GameData data);
        
};

#endif
