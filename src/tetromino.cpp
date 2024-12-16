#include "tetromino.hpp"
#include "constants.hpp"

void Tetromino::moveDir(int dir) {
    switch(dir){
        case 0:
            this->y += 1;
            this->rect.y += TILE_SIZE;
            break;
        case 1:
            this->x -= 1;
            this->rect.x -= TILE_SIZE;
            break;
        case -1:
            this->x += 1;
            this->rect.x += TILE_SIZE;
            break;
        case 3:
            this->y -= 1;
            this->rect.y -= TILE_SIZE;
            break;
    }
}

void Tetromino::moveTo(int x, int y) {
    this->x = x;
    this->y = y;
    this->rect.x = x;
    this->rect.y = y;
}
