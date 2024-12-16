#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "entity.hpp"

class Tetromino : public Entity {
    public:
        Tetromino(SDL_Color color, unsigned int shape[16])
            : Entity(4, 4) {
            this->color.r = color.r;
            this->color.g = color.g;
            this->color.b = color.b;
            this->color.a = color.a;
            for(int i = 0; i < 16; i++) this->tiles[i] = shape[i];
        };
        Tetromino() : Entity(4,4) {
            this->color.r = 255;
            this->color.g = 0;
            this->color.b = 0;
            this->color.a = 0;
            unsigned int shape[16] = {0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0};
            for(int i = 0; i < 16; i++) this->tiles[i] = shape[i];
        };
        void moveDir(int dir);
        void moveTo(int x, int y);
}; 

#endif
