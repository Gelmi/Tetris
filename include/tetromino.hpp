#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "entity.hpp"

class Tetromino : public Entity {
    public:
        Tetromino(SDL_Renderer * renderer, SDL_Color color, unsigned int shape[16])
            : Entity(renderer, (char *)"assets/tetristile.bmp", 4, 4) {
            this->color.r = color.r;
            this->color.g = color.g;
            this->color.b = color.b;
            this->color.a = color.a;
            for(int i = 0; i < 16; i++) this->tiles[i] = shape[i];
        };
};

#endif
