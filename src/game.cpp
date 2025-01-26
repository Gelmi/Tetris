/**
 * @file game.cpp
 * @author Gabriel and Guilherme
 * @brief This file handles the settings of the game looping
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include "gameview.hpp"
#include "gamedata.hpp"
#include "mockserver.hpp"
#include "constants.hpp"
#include "gameend.hpp"
#include "pause.hpp"
#include <memory>

void Game::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer; 
    this->close = 0;
    if(!window) std::cerr << "Game Didnt Receive Window" << SDL_GetError() << std::endl;
    if(!renderer) std::cerr << "Game Didnt Receive Renderer" << SDL_GetError() << std::endl;
}

int Game::GetInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                this->close = true;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_SPACE:
                        return SPACE_BAR;
                        break;
                    case SDLK_RIGHT: 
                        return ARROW_RIGHT;
                        break;
                    case SDLK_LEFT:
                        return ARROW_LEFT;
                        break;
                    case SDLK_UP:
                        return ARROW_UP;
                        break;
                    case SDLK_DOWN:
                        return ARROW_DOWN;
                        break;
                    case SDLK_c:
                        return SWAP;
                        break;
                    case SDLK_ESCAPE:
                        this->running = false;
                        return 0;
                        break;
                    default:
                        return 0;
                }
                break;
        }
        return 0;
    }
    return 0;
}

void Game::PauseMenu() {
    std::unique_ptr<Pause> pause = std::make_unique<Pause>(this->window, this->renderer);
    pause->Setup(this->window, this->renderer);
    int pausechoice = pause->showpause();
    switch (pausechoice) {
        case 0:
            this->running = true;
            break;
        case 1:
            this->close = true;
            this->running = true;
            break;
    }
}

void Game::gameEndMenu() {
    std::unique_ptr<GameEnd> gameEnd = std::make_unique<GameEnd>(this->window, this->renderer);
    gameEnd->Setup(this->window, this->renderer);
    int choice = gameEnd->showgameend();
    switch (choice) {
        case 1:
            this->close = true;
            this->running = true;
            break;
    }
}

int Game::Run(){ 
    GameData gameData;
    std::unique_ptr<GameView> gameView = std::make_unique<GameView>(this->window, this->renderer);
    std::unique_ptr<MockServer> mockServer = std::make_unique<MockServer>();
    while(!this->close){
        while(!running) Game::PauseMenu();
        lose = mockServer->update(Game::GetInput(), gameData);     
        gameData = mockServer->getState();
        if(!this->close) gameView->Draw(gameData);
        if(lose) Game::gameEndMenu();
    };
    return 0;
}
