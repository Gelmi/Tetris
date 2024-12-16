#include "board.hpp"

int Board::isPositionValid(Tetromino Tetromino) {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            if(Tetromino.getTiles()[Tetromino.atPos(i, j)] != 0){    
                if(this->tiles[this->atPos(Tetromino.getX()+j, Tetromino.getY()+i)] != 0){ 
                    printf("Block found in: %d, %d\n", Tetromino.getX()+j, Tetromino.getY()+i);
                    return 2;
                }
            if(Tetromino.getX() + j < 0 || Tetromino.getX() + j > 9 || Tetromino.getY() + i > 19) {
                    printf("%d\n", Tetromino.getY()+i);
                    return 1;
                }
            }
        }
    }
    return 0;
} 

void Board::lockTetromino(Tetromino Tetromino) {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            this->tiles[this->atPos(Tetromino.getX()+j, Tetromino.getY()+i)] = Tetromino.getTiles()[Tetromino.atPos(i,j)];
        }
    }
}
