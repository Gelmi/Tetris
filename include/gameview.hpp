#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SDL.h>
#include "gamedata.hpp"
#include "application.hpp"

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
        GameView(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer); // Novo construtor

        void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer);
        ~GameView();
        void Draw(GameData data);
        
};

#endif
