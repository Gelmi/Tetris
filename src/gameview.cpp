#include "application.hpp"
#include "gameview.hpp"
#include <SDL.h>
#include <iostream>
#include "constants.hpp"

GameView::GameView(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;

    if (!window || !renderer) {
        std::cerr << "Error creating GameView: " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->boardTexture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10*32, 20*32);
    SDL_Surface * image = SDL_LoadBMP("assets/boardtile.bmp");
    if(!image) {
        std::cout << "Error loading image boardtile.bmp" << SDL_GetError() << std::endl;
    }
    this->boardTileTexture = SDL_CreateTextureFromSurface(this->renderer, image);
    if(!(this->boardTileTexture)) {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(image);
    this->tetrominoTexture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 4*32, 4*32);
    SDL_Surface * imageT = SDL_LoadBMP("assets/tetristile.bmp");
    if(!imageT) {
        std::cout << "Error loading image boardtile.bmp" << SDL_GetError() << std::endl;
    }
    this->tetrominoTileTexture = SDL_CreateTextureFromSurface(this->renderer, imageT);
    if(!(this->tetrominoTileTexture)) {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(imageT);
}

GameView::~GameView() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(this->boardTileTexture);
    SDL_DestroyTexture(this->boardTexture);
    SDL_DestroyTexture(this->tetrominoTexture);
    SDL_DestroyTexture(this->tetrominoTileTexture);
}

void GameView::Draw(GameData data) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);        
    GameView::DrawBoard(data);
    SDL_RenderPresent(renderer); 
}

int atPos(int x, int y, int h) {
    return (y*h)+x;
}

void GameView::DrawBoard(GameData data) {
    SDL_SetTextureBlendMode(this->boardTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(this->renderer, this->boardTexture);
    SDL_SetTextureColorMod(this->boardTileTexture, 255, 255, 255);
    SDL_Rect tileRect;
    tileRect.w = TILE_SIZE;
    tileRect.h = TILE_SIZE;
    for(int j = 0; j < 20; j++) {
        for(int i = 0; i < 10; i++) {
            tileRect.x = i * TILE_SIZE;
            tileRect.y = j * TILE_SIZE;
            switch(data.board[atPos(i, j, 10)]){
                case 0:
                    SDL_RenderCopy(renderer, this->boardTileTexture, NULL, &tileRect);
                    break;
                case 1:
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 0, 255, 255);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
                case 2: 
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 255, 255, 0);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
                case 3: 
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 128, 0, 128);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
                case 4: 
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 0, 0, 255);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
                case 5: 
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 255, 127, 0);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
                case 6: 
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 0, 255, 0);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
                case 7: 
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 255, 0, 0);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
            }
        }
    }
    SDL_SetRenderTarget(this->renderer, NULL);
    tileRect.x = 0;
    tileRect.y = 0;
    tileRect.w = 10 * TILE_SIZE;
    tileRect.h = 20 * TILE_SIZE;
    SDL_RenderCopy(renderer, boardTexture, NULL, &tileRect);
}
