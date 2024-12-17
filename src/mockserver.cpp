#include "mockserver.hpp"

MockServer::MockServer() {
    this->board = Board();
    this->tetromino = TetrominoI();
    printf("%d\n", this->tetromino.getColor().r);
    for(int i = 0; i< 16; i++) printf("%d ", this->tetromino.getTiles()[i]);
    printf("\n");
    this->counter = 0;
}

void MockServer::update(int command) {
    this->counter = this->counter + 1; 
    if(command == 0) {
    } else if(command == 2) {
        while(board.isPositionValid(tetromino) == 0){
            tetromino.moveDir(0);
        }
        tetromino.moveDir(3);
    } else {
        tetromino.moveDir(command);
        int position = board.isPositionValid(tetromino);
        if(position != 0) tetromino.moveDir(-command);
        if(position == 2) {
            board.lockTetromino(tetromino);
            tetromino.moveTo(0,0);
        }
    }
    if(counter >= 1000){
        counter = 0;
        tetromino.moveDir(0);
        int position = board.isPositionValid(tetromino);
        if(position != 0) {
            tetromino.moveDir(3);
            board.lockTetromino(tetromino);
            tetromino.moveTo(0, 0);
        }
    }
}

GameData MockServer::getState(){
    GameData gameData;
    for(int i = 0; i < 200; i++) {
        gameData.board[i] = this->board.getTiles()[i];
        if(i<16) {
            gameData.tetromino[i] = this->tetromino.getTiles()[i];
        }
    }
    //printf("%d\n", this->tetromino.getColor().r);
    gameData.color = this->tetromino.getColor();
    gameData.x = tetromino.getRect()->x;
    gameData.y = tetromino.getRect()->y;
    return gameData;
}
