/**
 * @file tetromino.cpp
 * @author Gabriel and Guilherme
 * @brief This files handles all the game pieces 
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "tetromino.hpp"
#include "constants.hpp"

/**
 * @brief Moves the Tetromino in a specified direction.
 * 
 * The function updates both the Tetromino's x and y coordinates and the 
 * associated SDL_Rect, which is used for rendering. The direction is 
 * determined by the \p dir parameter:
 * - 0: Move down
 * - 1: Move left
 * - -1: Move right
 * - 3: Move up
 * 
 * @param dir An integer representing the direction to move.
 */
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

/**
 * @brief Moves the Tetromino to specific coordinates.
 * 
 * This function sets the Tetromino's x and y positions to the given 
 * coordinates and updates the position of its SDL_Rect accordingly.
 * 
 * @param x The new x-coordinate for the Tetromino.
 * @param y The new y-coordinate for the Tetromino.
 */
void Tetromino::moveTo(int x, int y) {
    this->x = x;
    this->y = y;
    this->rect.x = x;
    this->rect.y = y;
}

/**
 * @brief Retrieves the color of the Tetromino.
 * 
 * This function returns the SDL_Color structure used to render 
 * the Tetromino, which contains RGBA color information.
 * 
 * @return An SDL_Color representing the Tetromino's color.
 */
SDL_Color Tetromino::getColor() {
    return this->color;
}

/**
 * @brief Gets the current rotation state of the Tetromino.
 * 
 * The rotation value can be from 0 to 3 and is used to index 
 * different orientations of the Tetromino shape.
 * 
 * @return An integer representing the current rotation (0-3).
 */
int Tetromino::getRotation() {
    return this->rotation;
}

/**
 * @brief Rotates the Tetromino to the left (counter-clockwise) without wall kicks.
 * 
 * This function modifies the Tetromino's rotation value by moving 
 * it to the left (counter-clockwise) one step. It does not perform 
 * any movement adjustments other than updating the rotation index.
 */
void Tetromino::rotateLeftPad(){
    this->rotation = (this->rotation + 3) % 4;    
}

/**
 * @brief Rotates the Tetromino to the right (clockwise) without wall kicks.
 * 
 * This function modifies the Tetromino's rotation value by moving 
 * it to the right (clockwise) one step. It does not perform any 
 * movement adjustments other than updating the rotation index.
 */
void Tetromino::rotateRightPad(){
    this->rotation = (this->rotation + 1) % 4;
} 

/**
 * @brief Rotates the Tetromino to the left (counter-clockwise) and adjusts its position.
 * 
 * This function changes the Tetromino's rotation state to the left 
 * (counter-clockwise) and then moves it one tile in a specific direction 
 * based on the new rotation. This simulates a "soft" wall kick.
 */
void Tetromino::rotateLeft(){
    this->rotation = (this->rotation + 3) % 4;    
    switch(this->rotation) {
        case 0:
            this->moveDir(1);
            break;
        case 1:
            this->moveDir(0);
            break;
        case 2:
            this->moveDir(-1);
            break;
        case 3:
            this->moveDir(3);
            break;
    }
}

/**
 * @brief Rotates the Tetromino to the right (clockwise) and adjusts its position.
 * 
 * This function changes the Tetromino's rotation state to the right 
 * (clockwise) and then moves it one tile in a specific direction 
 * based on the new rotation. This simulates a "soft" wall kick.
 */
void Tetromino::rotateRight(){
    this->rotation = (this->rotation + 1) % 4;
    switch(this->rotation) {
        case 0:
            this->moveDir(0); 
            printf("Cima\n");
            break;
        case 1:
            this->moveDir(-1);
            break;
        case 2:
            this->moveDir(3);
            break;
        case 3:
            this->moveDir(1);
            break;
    }
}

/**
 * @brief Calculates the tile index within the Tetromino's shape for the given coordinates.
 * 
 * The Tetromino shape is stored as a 4x4 grid. Depending on the current 
 * rotation, the coordinates are mapped to a different index in this grid. 
 * 
 * @param x The x-coordinate in the 4x4 grid of the Tetromino.
 * @param y The y-coordinate in the 4x4 grid of the Tetromino.
 * @return An integer index into the 4x4 tile array representing the Tetromino's shape.
 */
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

/**
 * @brief Factory method to create new Tetromino objects based on type.
 * 
 * This function returns a pointer to a derived Tetromino class 
 * based on the given \p type:
 * - 1: TetrominoI
 * - 2: TetrominoO
 * - 3: TetrominoT
 * - 4: TetrominoJ
 * - 5: TetrominoL
 * - 6: TetrominoS
 * - 7: TetrominoZ
 * 
 * @param type An integer representing the type of Tetromino to create.
 * @return A pointer to the created Tetromino object.
 */
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

/**
 * @brief Overrides the default left rotation for the 'I' Tetromino.
 * 
 * This method calls the base implementation of rotateLeftPad(), 
 * indicating that the 'I' Tetromino has unique rotation behavior 
 * compared to other Tetromino types.
 */
void TetrominoI::rotateLeft() { Tetromino::rotateLeftPad(); };

/**
 * @brief Overrides the default right rotation for the 'I' Tetromino.
 * 
 * This method calls the base implementation of rotateRightPad(), 
 * indicating that the 'I' Tetromino has unique rotation behavior 
 * compared to other Tetromino types.
 */
void TetrominoI::rotateRight() { Tetromino::rotateRightPad(); };

/**
 * @brief Overrides the default left rotation for the 'O' Tetromino.
 * 
 * The 'O' Tetromino is a square and effectively does not change 
 * orientation, but this override still calls rotateLeftPad().
 */
void TetrominoO::rotateLeft() { Tetromino::rotateLeftPad(); };

/**
 * @brief Overrides the default right rotation for the 'O' Tetromino.
 * 
 * The 'O' Tetromino is a square and effectively does not change 
 * orientation, but this override still calls rotateRightPad().
 */
void TetrominoO::rotateRight() { Tetromino::rotateRightPad(); };
