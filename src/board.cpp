#include "board.hpp"

int Board::isPositionValid(Tetromino * Tetromino) {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            if(Tetromino->getTiles()[Tetromino->atPos(i, j)] != 0){    
                //Bateu em algum bloco ou embaixo
                if(Tetromino->getY() + i > 19 || this->tiles[this->atPos(Tetromino->getX()+j, Tetromino->getY()+i)] != 0){ 
                    //printf("Block found in: %d, %d\n", Tetromino->getX()+j, Tetromino->getY()+i);
                    return 2;
                }
                //Bateu nas laterais
                if(Tetromino->getX() + j < 0 || Tetromino->getX() + j > 9 ) {
                    //printf("%d\n", Tetromino->getY()+i);
                    return 1;
                }
            }
        }
    }
    return 0;
} 

void Board::lockTetromino(Tetromino * Tetromino) {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            if(Tetromino->getTiles()[Tetromino->atPos(i, j)] != 0)  
                this->tiles[this->atPos(Tetromino->getX()+j, Tetromino->getY()+i)] 
                    = Tetromino->getTiles()[Tetromino->atPos(i,j)];
        }
    }
    this->cleanRows(Tetromino);
}

void Board::cleanRows(Tetromino * Tetromino) {
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
    printf("LINHAS: %d\n", n);
    if(n > 0) this->addScore(n);
    rows = rows + n;
    if(this->rows >= 10) {
        this->level++;
        rows = rows - 10;
    }
    printf("====================\nscore: %d\nlevel: %d\nrows: %d\n", this->score, level, rows);
} 

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
