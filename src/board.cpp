/**
 * @file board.cpp
 * @author Gabriel and Guilherme 
 * @brief This file handles the board settings 
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "board.hpp"

/**
 * @brief implement function to validate Tetromino's position on the board
 * 
 * @param Tetromino 
 * @return int 
 */
int Board::isPositionValid(Tetromino * Tetromino) {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            if(Tetromino->getTiles()[Tetromino->atPos(i, j)] != 0){    
                //Bateu nas laterais
                if(Tetromino->getX() + j < 0 || Tetromino->getX() + j > 9 ) {
                    return 1;
                }
                //Bateu em algum bloco ou embaixo
                if(Tetromino->getX() + j > 0 && Tetromino->getY() + i > 0
                    && Tetromino->getY() + i > 19 || this->tiles[this->atPos(Tetromino->getX()+j, Tetromino->getY()+i)] != 0){ 
                    return 2;
                }
            }
        }
    }
    return 0;
} 

/**
 * @brief add function to check if the game has ended
 * 
 * @return true 
 * @return false 
 */
bool Board::checkIfEnded(){ 
    for(int i = 0; i < 10; i++){
        if(this->tiles[i] != 0) return true;
    }
    return false;
}


/**
 * @brief implement function to lock Tetromino on the board and clean rows
 * 
 * @param Tetromino 
 * @return int 
 */
int Board::lockTetromino(Tetromino * Tetromino) {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            if(Tetromino->getTiles()[Tetromino->atPos(i, j)] != 0)  
                this->tiles[this->atPos(Tetromino->getX()+j, Tetromino->getY()+i)] 
                    = Tetromino->getTiles()[Tetromino->atPos(i,j)];
        }
    }
    return this->cleanRows(Tetromino);
}


/**
 * @brief add function to clear full rows and update score
 * 
 * @param Tetromino 
 * @return int 
 */
int Board::cleanRows(Tetromino * Tetromino) {
    bool fullRow;
    int n = 0;
    for(int i = 0; i < 4; i++) {
        fullRow = true;
        for(int j = 0; j < 10; j++){
            if(this->tiles[this->atPos(j, Tetromino->getY()+i)] == 0) fullRow = false;
        }
        if(fullRow == true) { 
            for(int k = Tetromino->getY()+i; k > 0; k--) {
                for(int j = 0; j < 10; j++){
                    this->tiles[this->atPos(j, k)] = this->tiles[this->atPos(j, k - 1)];
                }
            }
            n++; 
        }
    }
    if(n > 0) this->addScore(n);
    rows = rows + n;
    if(this->rows >= 10) {
        this->level++;
        rows = rows - 10;
    }
    return n;
} 

/**
 * @brief implement function to add penalty rows with random gaps
 * 
 * @param n 
 */
void Board::addRows(int n) {
    for(int i = 0; i < 20 - n; i++) {
        for(int j = 0; j < 10; j++) {
            this->tiles[this->atPos(j, i)] =
                this->tiles[this->atPos(j, i+n)]; 
        }
    }
    int empty = rand() % 9 + 1;
    for(int i = 20 - n; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            if(j == empty) this->tiles[this->atPos(j, i)] = 0;
            else this->tiles[this->atPos(j, i)] = 8;
        }
    } 
}

/**
 * @brief feat(board): add scoring mechanism based on cleared rows
 * 
 * @param n 
 */
void Board::addScore(int n) {
    int p;
    switch(n) {
        case 1:
            p = 40;
            break;
        case 2:
            p = 100;
            break;
        case 3:
            p = 300;
            break;
        case 4:
            p = 1200;
            break;
    }
    printf("%d\n", p);
    this->score = this->score + (p*(this->level+1));
} 
