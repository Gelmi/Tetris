#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include "entity.hpp"

class Tetromino : public Entity {
    public:
        Tetromino(SDL_Color color, std::array<unsigned int, 16> shape)
            : Entity(4, 4) {
            this->color.r = color.r;
            this->color.g = color.g;
            this->color.b = color.b;
            this->color.a = color.a;
            for(int i = 0; i < 16; i++) this->tiles[i] = shape[i];
        }; 
        void moveDir(int dir);
        void moveTo(int x, int y);
        SDL_Color getColor();
}; 

class TetrominoI : public Tetromino {
    public:
        TetrominoI() : Tetromino({52,235,235,255}, {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}) {}; 
};

class TetrominoL : public Tetromino {
    public:
        TetrominoL() : Tetromino({52,235,235,255}, {0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1}) {}; 
};

#endif
