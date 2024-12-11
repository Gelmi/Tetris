#include "entity.hpp"

#include<cstring>
#include<SDL.h>
#include<iostream>

Entity::Entity(SDL_Renderer* renderer, char path[30], int w, int h){
    this->renderer = renderer;
    this->w = w;
    this->h = h;
    tiles = new unsigned int[w * h];
    for(int i = 0; i < (w * h); i++) tiles[i] = 1;
    strcpy(this->path, path);
    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*32, h*32);
    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    this->dst.h = h*32;
    this->dst.w = w*32;
    this->dst.x = 0;
    this->dst.y = 0;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
}

Entity::~Entity(){
    SDL_DestroyTexture(texture);
}

void Entity::setSize(int w, int h) {
    dst.w = w*32;
    dst.h = h*32;
}

void Entity::setPosition(int x, int y) {
    dst.x = x;
    dst.y = y;
}

int Entity::atPos(int x, int y) {
    return (y*this->h)+x;
}

void Entity::Draw() {
    SDL_SetRenderTarget(this->renderer, this->texture);
    SDL_Surface * image = SDL_LoadBMP(this->path);
    if(!image) {
        std::cout << "Error loading image boardtile.bmp" << SDL_GetError() << std::endl;
    }
    SDL_Texture * tileTexture = SDL_CreateTextureFromSurface(this->renderer, image);
    if(!tileTexture) {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    SDL_SetTextureColorMod(tileTexture, color.r, color.g, color.b);
    SDL_FreeSurface(image);
    SDL_Rect tileRect;
    tileRect.w = 32;
    tileRect.h = 32;
    for(int j = 0; j < this->h; j++) {
        for(int i = 0; i < this->w; i++) {
            //std::cout << this->atPos(i, j) << std::endl;
            if(tiles[this->atPos(j, i)] != 0){
                tileRect.x = i * 32;
                tileRect.y = j * 32;
                SDL_RenderCopy(renderer, tileTexture, NULL, &tileRect);
            }
        }
    }
    SDL_DestroyTexture(tileTexture);
    SDL_SetRenderTarget(this->renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}
