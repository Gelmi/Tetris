#include "entity.hpp"

#include<cstring>
#include<SDL.h>
#include<iostream>

Entity::Entity(SDL_Renderer* renderer, char path[30]){
    this->renderer = renderer;
    image = SDL_LoadBMP(path);
    if(!image) {
        std::cout << "Error loading image boardtile.bmp" << SDL_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(this->renderer, image);
    if(!texture) {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(image);
    dst.h = 32;
    dst.w = 32;
    dst.x = 0;
    dst.y = 0;
}

Entity::~Entity(){
    SDL_DestroyTexture(texture);
}

void Entity::setSize(int w, int h) {
    dst.w = w;
    dst.h = h;
}

void Entity::setPosition(int x, int y) {
    dst.x = x;
    dst.y = y;
}

void Entity::Draw() {
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}
