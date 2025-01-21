#ifndef BOARD_HPP
#define BOARD_HPP

#include "entity.hpp"
#include "tetromino.hpp"

class Board : public Entity {
    private:
        int level, score, rows;
    public:
        Board():Entity(10, 20), level(0), score(0), rows(0){};
        int isPositionValid(Tetromino * Tetromino);
        void lockTetromino(Tetromino * Tetromino);
        void cleanRows(Tetromino * Tetromino);
        void addScore(int n);
        int getLevel() { return level; };
        int getScore() { return score; };
        int getRows() { return rows; };
};

#endif 
