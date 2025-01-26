#include "gameview.hpp"
#include <SDL.h>
#include <iostream>
#include "constants.hpp"
#include <SDL_ttf.h>

GameView::GameView(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    if(TTF_Init() == -1){
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
    }

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
    this->font = TTF_OpenFont("./assets/Roboto.ttf", 20);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
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
    GameView::DrawEntity(boardTexture, tetrominoTileTexture, boardTileTexture,
            TILE_SIZE, data.board, 0, 0, 20, 10);
    GameView::DrawStats(data);
    GameView::DrawEntity(tetrominoTexture, tetrominoTileTexture, NULL,
            TILE_SIZE, data.tiles, 340, 100, 4, 4);
    SDL_RenderPresent(this->renderer); 
}

int atPos(int x, int y, int h) {
    return (y*h)+x;
}

void GameView::DrawStats(GameData data) {
    std::string score_text = "Score: " + std::to_string(data.score) + ", " +
                             "Level: " + std::to_string(data.level) + ", " +
                             "Rows: " + std::to_string(data.rows);
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

void GameView::DrawEntity(SDL_Texture * texture, SDL_Texture * tileTexture, 
        SDL_Texture * backTexture, int tileSize, int * tiles, int x, int y, int h, int w) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(this->renderer, texture);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
    SDL_SetTextureColorMod(tileTexture, 255, 255, 255);
    SDL_Rect tileRect;
    tileRect.w = tileSize;
    tileRect.h = tileSize;
    for(int j = 0; j < h; j++) {
        for(int i = 0; i < w; i++) {
            tileRect.x = i * tileSize;
            tileRect.y = j * tileSize;
            switch(tiles[atPos(i, j, w)]){
                case 0: 
                    SDL_SetTextureColorMod(tileTexture, 0, 0, 0);
                    break;
                case 1:
                    SDL_SetTextureColorMod(tileTexture, 0, 255, 255);
                    break;
                case 2: 
                    SDL_SetTextureColorMod(tileTexture, 255, 255, 0);
                    break;
                case 3: 
                    SDL_SetTextureColorMod(tileTexture, 128, 0, 128);
                    break;
                case 4: 
                    SDL_SetTextureColorMod(tileTexture, 0, 0, 255);
                    break;
                case 5: 
                    SDL_SetTextureColorMod(tileTexture, 255, 127, 0);
                    break;
                case 6: 
                    SDL_SetTextureColorMod(tileTexture, 0, 255, 0);
                    break;
                case 7: 
                    SDL_SetTextureColorMod(tileTexture, 255, 0, 0);
                    break;
                case 8:
                    SDL_SetTextureColorMod(tileTexture, 200, 200, 200);
                    break;
            }
            if(backTexture != NULL) {
                if(tiles[atPos(i,j,w)] == 0) {
                    SDL_RenderCopy(renderer, backTexture, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(renderer, tileTexture, NULL, &tileRect);
                }
            } else {
                if(tiles[atPos(i,j,w)] != 0) {
                    SDL_RenderCopy(renderer, tileTexture, NULL, &tileRect);
                }
            };
        }
    }
    SDL_SetRenderTarget(this->renderer, NULL);
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = w * tileSize;
    tileRect.h = h * tileSize;
    SDL_RenderCopy(renderer, texture, NULL, &tileRect);
}
