#include "multigameview.hpp"
#include <SDL.h>
#include <iostream>
#include "constants.hpp"
#include <SDL_ttf.h>

MultiGameView::MultiGameView(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    if(TTF_Init() == -1){
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
    }

    this->window = sharedWindow;
    this->renderer = sharedRenderer;

    if (!window || !renderer) {
        std::cerr << "Error creating MultiGameView: " << SDL_GetError() << std::endl;
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
    this->font = TTF_OpenFont("./assets/Roboto.ttf", 20);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}

MultiGameView::~MultiGameView() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(this->boardTileTexture);
    SDL_DestroyTexture(this->boardTexture);
    SDL_DestroyTexture(this->tetrominoTexture);
    SDL_DestroyTexture(this->tetrominoTileTexture);
}

void MultiGameView::Draw(GameData data) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);        
    MultiGameView::DrawBoard(data);
    MultiGameView::DrawStats(data);
    MultiGameView::DrawNextTetromino(data);
    MultiGameView::DrawBoardOp(data);
    SDL_RenderPresent(this->renderer); 
}

void MultiGameView::DrawWait(GameData data) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);        
    SDL_RenderPresent(this->renderer); 
}


int MultiGameView::atPos(int x, int y, int h) {
    return (y*h)+x;
}

void MultiGameView::DrawStats(GameData data) {
    std::string score_text = "Score: " + std::to_string(data.score) + ", " +
                             "Level: " + std::to_string(data.level);
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, score_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_Rect renderQuad = { 325, 20, text_width, text_height };
    SDL_RenderCopy(this->renderer, text, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
}

void MultiGameView::DrawBoard(GameData data) {
    SDL_SetTextureBlendMode(this->boardTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(this->renderer, this->boardTexture);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
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
                case 8:
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 200, 200, 200);
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

void MultiGameView::DrawNextTetromino(GameData data) {
    SDL_SetTextureBlendMode(this->tetrominoTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(this->renderer, this->tetrominoTexture);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
    SDL_Rect tileRect;
    tileRect.w = TILE_SIZE;
    tileRect.h = TILE_SIZE;
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            if(data.tiles[atPos(j, i, 4)] != 0){
                tileRect.x = (i * TILE_SIZE);
                tileRect.y = (j * TILE_SIZE);
                switch(data.tiles[atPos(i, j, 4)]){
                    case 0:
                        SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
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
                    case 8:
                        SDL_SetTextureColorMod(this->tetrominoTileTexture, 200, 200, 200);
                        SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                        break;
                }
            }
        }
    }
    SDL_SetRenderTarget(this->renderer, NULL);
    tileRect.x = 340;
    tileRect.y = 100;
    tileRect.w = TILE_SIZE*4;
    tileRect.h = TILE_SIZE*4;
    SDL_RenderCopy(renderer, this->tetrominoTexture, NULL, &tileRect);
}

void MultiGameView::DrawBoardOp(GameData data) {
    SDL_SetTextureBlendMode(this->boardTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(this->renderer, this->boardTexture);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
    SDL_SetTextureColorMod(this->boardTileTexture, 255, 255, 255);
    SDL_Rect tileRect;
    tileRect.w = TILE_SIZE_OP;
    tileRect.h = TILE_SIZE_OP;
    for(int j = 0; j < 20; j++) {
        for(int i = 0; i < 10; i++) {
            tileRect.x = i * TILE_SIZE_OP;
            tileRect.y = j * TILE_SIZE_OP;
            switch(data.boardOp[atPos(i, j, 10)]){
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
                case 8:
                    SDL_SetTextureColorMod(this->tetrominoTileTexture, 200, 200, 200);
                    SDL_RenderCopy(renderer, this->tetrominoTileTexture, NULL, &tileRect);
                    break;
            }
        }
    }
    SDL_SetRenderTarget(this->renderer, NULL);
    tileRect.x = 340;
    tileRect.y = 280;
    tileRect.w = 10 * TILE_SIZE_OP;
    tileRect.h = 20 * TILE_SIZE_OP;
    SDL_RenderCopy(renderer, boardTexture, NULL, &tileRect);
}
