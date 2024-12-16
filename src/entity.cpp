#include "entity.hpp"

#include<cstring>
#include<SDL.h>
#include "constants.hpp"

Entity::Entity(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    tiles = new unsigned int[w * h];
    for(int i = 0; i < (w * h); i++) tiles[i] = 0;
    this->rect.h = h*TILE_SIZE;
    this->rect.w = w*TILE_SIZE;
    this->rect.x = x;
    this->rect.y = y;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
}

SDL_Rect * Entity::getRect() {
    return &(this->rect);
}

unsigned int * Entity::getTiles() {
    return this->tiles;
}

int Entity::atPos(int x, int y) {
    return (y*this->w)+x;
}

int Entity::getX(){
    return this->x;
}

int Entity::getY(){
    return this->y;
}
