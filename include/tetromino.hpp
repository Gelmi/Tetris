#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include "entity.hpp"

class Tetromino : public Entity {
    protected:
        int rotation;

    public:
        Tetromino(SDL_Color color, std::array<unsigned int, 16> shape)
            : Entity(4, 4), rotation(0) {
            this->color.r = color.r;
            this->color.g = color.g;
            this->color.b = color.b;
            this->color.a = color.a;
            for(int i = 0; i < 16; i++) this->tiles[i] = shape[i];
        }; 
        void moveDir(int dir);
        void moveTo(int x, int y);
        void rotateLeft();
        void rotateRight();
        SDL_Color getColor();
        int getRotation();
        static Tetromino * create(int type);
        int atPos(int x, int y);
}; 

class TetrominoI : public Tetromino {
    public:
        TetrominoI() : Tetromino({0,255,255,255}, {0,0,0,0,
                                                   1,1,1,1,
                                                   0,0,0,0,
                                                   0,0,0,0}) {}; 
};

class TetrominoO : public Tetromino {
    public:
        TetrominoO() : Tetromino({255,255,0,255}, {0,0,0,0,
                                                   0,2,2,0,
                                                   0,2,2,0,
                                                   0,0,0,0}) {}; 
}; 

class TetrominoT : public Tetromino {
    public:
        TetrominoT() : Tetromino({128,0,128,255}, {0,0,0,0,
                                                   0,3,0,0,
                                                   0,3,3,0,
                                                   0,3,0,0}) {}; 
};

class TetrominoJ : public Tetromino {
    public:
        TetrominoJ() : Tetromino({0,0,255,255}, {0,0,0,0,
                                                 0,0,4,0,
                                                 4,4,4,0,
                                                 0,0,0,0}) {}; 
};

class TetrominoL : public Tetromino {
    public:
        TetrominoL() : Tetromino({255,127,0,255}, {0,0,0,0,
                                                   5,5,5,0,
                                                   0,0,5,0,
                                                   0,0,0,0}) {}; 
};

class TetrominoS : public Tetromino {
    public:
        TetrominoS() : Tetromino({0,255,0,255}, {0,0,0,0,
                                                 0,0,6,0,
                                                 0,6,6,0,
                                                 0,6,0,0}) {}; 
};

class TetrominoZ : public Tetromino {
    public:
        TetrominoZ() : Tetromino({255,0,0,255}, {0,0,0,0,
                                                 0,7,0,0,
                                                 0,7,7,0,
                                                 0,0,7,0}) {}; 
};

#endif
