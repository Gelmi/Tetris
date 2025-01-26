/**
 * @file entity.cpp
 * @author Gabriel and Guilherme
 * @brief This file handles the manager of the pieces
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "entity.hpp"

#include<cstring>
#include<SDL.h>
#include "constants.hpp"
#include <stdio.h>

/**
 * @brief Construct a new Entity:: Entity object
 implement destructor to free dynamically allocated memory
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 */
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

/**
 * @brief Destroy the Entity:: Entity object
 * 
 */
Entity::~Entity() {
    delete tiles;
}

/**
 * @brief add function to get the SDL_Rect of the entity
 * 
 * @return SDL_Rect* 
 */
SDL_Rect * Entity::getRect() {
    return &(this->rect);
}

/**
 * @brief add function to access the entity's tile array
 * 
 * @return unsigned int* 
 */
unsigned int * Entity::getTiles() {
    return this->tiles;
}

/**
 * @brief add helper function to calculate tile position in the array
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int Entity::atPos(int x, int y) {
    return (y*this->w)+x;
}

/**
 * @brief add getter functions for entity's x and y positions
 * 
 * @return int 
 */
int Entity::getX(){
    return this->x;
}

int Entity::getY(){
    return this->y;
}
