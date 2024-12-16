#include "mockserver.hpp"

MockServer::MockServer() {
    this->board = Board();
    this->tetromino = Tetromino();
    this->counter = 0;
    this->board.getTiles()[199] = 1;
    this->board.getTiles()[198] = 1;
    this->board.getTiles()[197] = 2;
}

void MockServer::update(int command) {
    this->counter = this->counter + 1; 
    if(command == 0) {
    } else {
        tetromino.moveDir(command);
        int position = board.isPositionValid(tetromino);
        if(position != 0) tetromino.moveDir(-command);
        if(position == 2) tetromino.moveTo(0,0);
    }
    if(counter >= 1000){
        counter = 0;
        tetromino.moveDir(0);
        if(board.isPositionValid(tetromino) != 0) tetromino.moveDir(3);

    }
}

GameData MockServer::getState(){
    GameData gameData;
    for(int i = 0; i < 200; i++) {
        gameData.board[i] = this->board.getTiles()[i];
        if(i<16) gameData.tetromino[i] = this->tetromino.getTiles()[i];
    }
    gameData.x = tetromino.getRect()->x;
    gameData.y = tetromino.getRect()->y;
    return gameData;
}
