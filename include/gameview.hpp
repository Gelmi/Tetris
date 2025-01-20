#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SDL.h>
#include "gamedata.hpp"

class GameView {
    private:
        SDL_Renderer * renderer;
        SDL_Window * window;
        SDL_Texture * boardTexture;
        SDL_Texture * boardTileTexture;
        SDL_Texture * tetrominoTexture;
        SDL_Texture * tetrominoTileTexture;
        
        void DrawBoard(GameData data);
        void DrawTetromino(GameData data);

    public:
        GameView();
        ~GameView();
        void Draw(GameData data);
        
};

#endif
