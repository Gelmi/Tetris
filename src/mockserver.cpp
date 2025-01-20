#include "mockserver.hpp"
#include <cstdlib>
#include "constants.hpp"
#include <math.h>

MockServer::MockServer() {
    this->board = new Board();
    this->tetromino = Tetromino::create(rand() % 7 + 1);
    printf("%d\n", this->tetromino->getColor().r);
    for(int i = 0; i< 16; i++) printf("%d ", this->tetromino->getTiles()[i]);
    printf("\n");
    this->counter = SDL_GetTicks();
}

void MockServer::lockAndLoad() {
    this->board->lockTetromino(this->tetromino);
    this->tetromino->moveTo(0,0);
    delete this->tetromino;
    this->tetromino = Tetromino::create(rand() % 7 + 1);
    // Line Clear Function
}

void MockServer::update(int command, GameData data) { 
    int position;
    switch(command) {
        case SPACE_BAR:
            while(board->isPositionValid(tetromino) == 0){
                tetromino->moveDir(0);
            }
            tetromino->moveDir(3);
            MockServer::lockAndLoad();
            break;
        case ARROW_LEFT:
        case ARROW_RIGHT:
            tetromino->moveDir(command);
            position = board->isPositionValid(tetromino);
            if(position != 0) tetromino->moveDir(-command);
            if(position == 2) MockServer::lockAndLoad();            
            break;
        case ARROW_UP: 
            tetromino->rotateLeft();
            position = board->isPositionValid(tetromino);
            if(position != 0) tetromino->rotateRight();
            break;
        case ARROW_DOWN:
            tetromino->rotateRight();         
            position = board->isPositionValid(tetromino);
            if(position != 0) tetromino->rotateLeft();
            break;
    }
    if(SDL_GetTicks() - this->counter >= pow(0.8-((data.level)*0.007), data.level)*1000){
        counter = SDL_GetTicks();
        tetromino->moveDir(0);
        int position = board->isPositionValid(tetromino);
        if(position != 0) {
            tetromino->moveDir(3);
            MockServer::lockAndLoad();
        }
    }
}

GameData MockServer::getState(){
    GameData gameData;
    gameData.score = this->board->getScore();
    gameData.level = this->board->getLevel();
    gameData.rows = this->board->getRows();
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
