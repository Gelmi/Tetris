/**
 * @file mockserver.cpp
 * @author Gabriel and Guilherme 
 * @brief This file handles all the data of the program
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "mockserver.hpp"
#include <cstdlib>
#include "constants.hpp"
#include <math.h>
#include <memory>

MockServer::MockServer() {
    this->board = std::make_unique<Board>();
    this->tetromino.reset(Tetromino::create(rand() % 7 + 2));
    this->nextTetromino.reset(Tetromino::create(rand() % 7 + 2));
    this->counter = SDL_GetTicks();
    this->hasSwaped = false; 
}

bool MockServer::lockAndLoad() {
    this->board->lockTetromino(this->tetromino.get());
    this->tetromino.swap(this->nextTetromino);
    this->nextTetromino.reset(Tetromino::create(rand() % 7 + 1));
    this->hasSwaped = false;
    if(this->board->isPositionValid(tetromino.get()) == 2) {
        return true;     
    }
    return false;
}

bool MockServer::update(int command, GameData data) { 
    int position;
    bool gameEnd = false;
    switch(command) {
        case SPACE_BAR:
            while(board->isPositionValid(tetromino.get()) == 0){
                tetromino->moveDir(0);
            }
            tetromino->moveDir(3);
            gameEnd = MockServer::lockAndLoad();
            break;
        case ARROW_LEFT:
        case ARROW_RIGHT:
            tetromino->moveDir(command);
            position = board->isPositionValid(tetromino.get());
            if(position != 0) tetromino->moveDir(-command);
            if(position == 2) gameEnd = MockServer::lockAndLoad();            
            break;
        case ARROW_UP: 
            tetromino->rotateLeft();
            position = board->isPositionValid(tetromino.get());
            if(position != 0) {
                tetromino->moveDir(1);
                position = board->isPositionValid(tetromino.get());
                if(position != 0) {
                    tetromino->moveDir(-1);
                    tetromino->moveDir(-1);
                    position = board->isPositionValid(tetromino.get());
                    if(position != 0) {
                        tetromino->moveDir(1);
                        tetromino->rotateRight();
                    }
                }
            }
            break;
        case ARROW_DOWN:
            //tetromino->rotateRight();         
            //position = board->isPositionValid(tetromino.get());
            //if(position != 0) tetromino->rotateLeft();
            tetromino->rotateRight();
            position = board->isPositionValid(tetromino.get());
            if(position != 0) {
                tetromino->moveDir(1);
                position = board->isPositionValid(tetromino.get());
                if(position != 0) {
                    tetromino->moveDir(-1);
                    tetromino->moveDir(-1);
                    position = board->isPositionValid(tetromino.get());
                    if(position != 0) {
                        tetromino->moveDir(1);
                        tetromino->rotateLeft();
                    }
                }
            }
            break;
        case SWAP:
            if(!hasSwaped) { 
                this->nextTetromino->moveTo(this->tetromino->getX(), this->tetromino->getY());
                this->tetromino->moveTo(3,0);
                this->tetromino.swap(this->nextTetromino);
                this->hasSwaped = true;
            }
            break;
    }
    if(SDL_GetTicks() - this->counter >= pow(0.8-((data.level)*0.007), data.level)*1000){
        counter = SDL_GetTicks();
        tetromino->moveDir(0);
        int position = board->isPositionValid(tetromino.get());
        if(position != 0) {
            tetromino->moveDir(3);
            gameEnd = MockServer::lockAndLoad();
        }
    }
    return gameEnd;
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
            gameData.tiles[this->nextTetromino->atPos(i,j)] = this->nextTetromino->getTiles()[this->nextTetromino->atPos(i,j)];
        }
    }
    return gameData;
}
