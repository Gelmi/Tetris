#ifndef MULTIGAMEVIEW_HPP
#define MULTIGAMEVIEW_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "gamedata.hpp"

class MultiGameView {
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
        void DrawBoardOp(GameData data);
        int atPos(int x, int y, int h);

    public:
        MultiGameView(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer);
        ~MultiGameView();
        void Draw(GameData data);
        void DrawWait(GameData data);
        
};

#endif
