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

SDL_Color Tetromino::getColor() {
    return this->color;
}

int Tetromino::getRotation() {
    return this->rotation;
}

void Tetromino::rotateLeft(){
    this->rotation = (this->rotation + 3) % 4;
}

void Tetromino::rotateRight(){
    this->rotation = (this->rotation + 1) % 4;
}

int Tetromino::atPos(int x, int y) {
    switch(this->rotation) {
        case 0:
            return (y*4)+x;
            break;
        case 1:
            return 12 + y - (x * 4);
            break;
        case 2:
            return 15 - (y * 4) - x;
            break;
        case 3:
            return 3 - y + (x * 4);
            break;
        default:
            return (y*4)+x;
    }
}

Tetromino * Tetromino::create(int type) {
    switch(type) {
        case 1:
            return new TetrominoI;
            break;
        case 2:
            return new TetrominoO;
            break;
        case 3:
            return new TetrominoT;
            break;
        case 4:
            return new TetrominoJ;
            break;
        case 5:
            return new TetrominoL;
            break;
        case 6:
            return new TetrominoS;
            break;
        case 7:
            return new TetrominoZ;
            break;
        default:
            return new TetrominoI;
    }
}
