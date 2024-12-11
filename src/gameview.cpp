#include "gameview.hpp"
#include <SDL.h>
#include <iostream>

GameView::GameView() {
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!window){
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
            system("pause");
    }
	if ( !renderer ) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
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
    GameView::DrawTetromino(data);
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
    tileRect.w = 32;
    tileRect.h = 32;
    for(int j = 0; j < 20; j++) {
        for(int i = 0; i < 10; i++) {
            //std::cout << this->atPos(i, j) << std::endl;
            if(data.board[atPos(j, i, 20)] != 0){
                tileRect.x = i * 32;
                tileRect.y = j * 32;
                SDL_RenderCopy(renderer, this->boardTileTexture, NULL, &tileRect);
            }
        }
    }
    SDL_SetRenderTarget(this->renderer, NULL);
    tileRect.x = 0;
    tileRect.y = 0;
    tileRect.w = 320;
    tileRect.h = 640;
    SDL_RenderCopy(renderer, boardTexture, NULL, &tileRect);
}

void GameView::DrawTetromino(GameData data) {
    SDL_SetTextureBlendMode(this->tetrominoTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(this->renderer, this->tetrominoTexture);
    SDL_SetTextureColorMod(this->tetrominoTileTexture, 255, 0, 0);
    SDL_Rect tileRect;
    tileRect.w = 32;
    tileRect.h = 32;
    for(int j = 0; j < 16; j++) {
        for(int i = 0; i < 16; i++) {
            if(data.tetromino[atPos(j, i, 4)] != 0){
                tileRect.x = (i * 32);
                tileRect.y = (j * 32);
                SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
            }
        }
    }
    SDL_SetRenderTarget(this->renderer, NULL);
    tileRect.x = data.x;
    tileRect.y = data.y;
    tileRect.w = 128;
    tileRect.h = 128;
    SDL_RenderCopy(renderer, this->tetrominoTexture, NULL, &tileRect);
}
