#ifndef BOARD_HPP
#define BOARD_HPP

#include "entity.hpp"

class Board : public Entity {
    public:
        Board(SDL_Renderer * renderer):Entity(renderer, (char *)"assets/boardtile.bmp", 10, 20){};
        bool isPositionValid(Entity Tetromino);
};

#endif
