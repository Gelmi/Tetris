#ifndef BOARD_HPP
#define BOARD_HPP

#include "entity.hpp"
#include "tetromino.hpp"

class Board : public Entity {
    public:
        Board():Entity(10, 20){};
        int isPositionValid(Tetromino * Tetromino);
        void lockTetromino(Tetromino * Tetromino);
};

#endif
