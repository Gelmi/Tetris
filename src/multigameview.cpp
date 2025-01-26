/**
 * @file multigameview.cpp
 * @author Gabriel and Guilherme
 * @brief This file handles the screen of multiplayer mode 
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "multigameview.hpp"
#include <SDL.h>
#include <iostream>
#include "constants.hpp"
#include <SDL_ttf.h>

/**
 * @brief Renders the current game state for multiplayer mode.
 *
 * This function clears the renderer, draws the local player's board,
 * the local player's next Tetromino, and the opponent's board.
 *
 * @param data A GameData structure containing information about both
 *        boards, scores, levels, and the next Tetromino.
 */
void MultiGameView::Draw(GameData data) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);        
    GameView::DrawEntity(boardTexture, tetrominoTileTexture, boardTileTexture,
            TILE_SIZE, data.board, 0, 0, 20, 10);
    GameView::DrawStats(data);
    GameView::DrawEntity(tetrominoTexture, tetrominoTileTexture, NULL,
            TILE_SIZE, data.tiles, 340, 100, 4, 4);
    GameView::DrawEntity(boardTexture, tetrominoTileTexture, boardTileTexture,
            TILE_SIZE_OP, data.boardOp, 340, 280, 20, 10);
    //SDL_RenderPresent(this->renderer); 
}

/**
 * @brief Displays a message indicating the client is waiting to connect to the server.
 *
 * This function clears the renderer and draws a centered text string 
 * "Waiting for connection to server".
 */
void MultiGameView::DrawWaitConnection() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);        
    std::string score_text = "Waiting for connection to server";
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, score_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_Rect renderQuad = { 400-(text_width/2), 320-(text_height/2), text_width, text_height };
    SDL_RenderCopy(this->renderer, text, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
    //SDL_RenderPresent(this->renderer); 
}

/**
 * @brief Displays a message indicating the client is waiting for the opponent to join or start.
 *
 * This function clears the renderer and draws a semi-transparent background
 * rectangle, then centers the text "Waiting the opponent" within it.
 */
void MultiGameView::DrawWaitStart() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    std::string score_text = "Waiting the opponent";
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, score_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_Rect renderQuad = { 400-(text_width/2), 320-(text_height/2), text_width, text_height };

    int rect_width = textSurface->w + 20;
    int rect_height = textSurface->h + 10;
    SDL_Rect rect = { 400-(rect_width/2), 320-(rect_height/2), rect_width, rect_height};
    SDL_RenderFillRect(this->renderer, &rect);
    SDL_RenderCopy(this->renderer, text, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
    //SDL_RenderPresent(this->renderer); 
}

/**
 * @brief Displays the result of the multiplayer game (win or lose).
 *
 * This function draws a message indicating whether the local player won or lost,
 * centered on a semi-transparent background rectangle.
 *
 * @param data A GameData structure that includes a boolean `result` 
 *        indicating if the local player has won (true) or lost (false).
 */
void MultiGameView::DrawResults(GameData data) {
    printf("Resultado: %s\n", data.result ? "true": "false");
    std::string score_text;
    if(data.result) score_text = "You win!";
    else score_text = "You lose!";
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, score_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_Rect renderQuad = { 400-(text_width/2), 320-(text_height/2), text_width, text_height };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int rect_width = textSurface->w + 20;
    int rect_height = textSurface->h + 10;
    SDL_Rect rect = { 400-(rect_width/2), 320-(rect_height/2), rect_width, rect_height};
    SDL_RenderFillRect(this->renderer, &rect);

    SDL_RenderCopy(this->renderer, text, NULL, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
    //SDL_RenderPresent(this->renderer); 
}

/**
 * @brief Destructor for MultiGameView.
 *
 * Closes the TTF font resource if it is open.
 */
MultiGameView::~MultiGameView(){
    if(font) TTF_CloseFont(font);
}
