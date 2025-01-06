#include "mockserver.hpp"
#include <cstdlib>
#include "constants.hpp"

MockServer::MockServer() {
    this->board = new Board();
    this->tetromino = Tetromino::create(rand() % 7 + 1);
    printf("%d\n", this->tetromino->getColor().r);
    for(int i = 0; i< 16; i++) printf("%d ", this->tetromino->getTiles()[i]);
    printf("\n");
    this->counter = SDL_GetTicks();
}

void MockServer::update(int command) { 
    if(command == SPACE_BAR) {
        while(board->isPositionValid(tetromino) == 0){
            tetromino->moveDir(0);
        }
        tetromino->moveDir(3);
        board->lockTetromino(tetromino);
        tetromino->moveTo(0,0);
        delete this->tetromino;
        this->tetromino = Tetromino::create(rand() % 7 + 1);
        printf("%d\n", rand() % 7);
        for(int i = 0; i< 16; i++) printf("%d ", this->tetromino->getTiles()[i]);
    } else if (command == ARROW_LEFT || command == ARROW_RIGHT) {
        tetromino->moveDir(command);
        int position = board->isPositionValid(tetromino);
        if(position != 0) tetromino->moveDir(-command);
        if(position == 2) {
            board->lockTetromino(tetromino);
            tetromino->moveTo(0,0);
            delete this->tetromino;
            this->tetromino = Tetromino::create(rand() % 7 + 1);
        }
    } else if (command == ARROW_UP) {
        tetromino->rotateLeft();
        int position = board->isPositionValid(tetromino);
        if(position != 0) tetromino->rotateRight();
        printf("Tetromino rot: %d\n", this->tetromino->getRotation());
    } else if (command == ARROW_DOWN) {
        tetromino->rotateRight();         
        int position = board->isPositionValid(tetromino);
        if(position != 0) tetromino->rotateLeft();
        printf("Tetromino rot: %d\n", this->tetromino->getRotation());
    }
    if(SDL_GetTicks() - this->counter >= 1000){
        counter = SDL_GetTicks();
        tetromino->moveDir(0);
        int position = board->isPositionValid(tetromino);
        if(position != 0) {
            tetromino->moveDir(3);
            board->lockTetromino(tetromino);
            tetromino->moveTo(0, 0);
            delete this->tetromino;
            this->tetromino = Tetromino::create(rand() % 7 + 1);
        }
    }
}

GameData MockServer::getState(){
    GameData gameData;
    for(int i = 0; i < 200; i++) {
        gameData.board[i] = this->board->getTiles()[i];  
    }
    // Pass tetromino data to board
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++) {
            if(this->tetromino->getTiles()[this->tetromino->atPos(i,j)] != 0) {
                gameData.board[this->board->atPos(this->tetromino->getX()+j, this->tetromino->getY()+i)]
                    = this->tetromino->getTiles()[this->tetromino->atPos(i,j)];
            }
        }
    }
    return gameData;
}
