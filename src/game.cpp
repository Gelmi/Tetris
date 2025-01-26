/**
 * @file game.cpp
 * @author Gabriel et Guilherme
 * @brief Ce fichier mis en place la boucle de le joue
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
#include "pause.hpp"
#include "application.hpp"

void Game::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer; 
    this->close = 0;
    this->running = true;
    if(!window) std::cerr << "Game Didnt Receive Window" << SDL_GetError() << std::endl;
    if(!renderer) std::cerr << "Game Didnt Receive Renderer" << SDL_GetError() << std::endl;
}

int Game::GetInput() {
    printf("A\n");
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                this->close = 1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_SPACE:
                        return 2;
                        break;
                    case SDLK_RIGHT: 
                        return -1;
                        break;
                    case SDLK_LEFT:
                        return 1;
                        break;
                    case SDLK_UP:
                        return 3;
                        break;
                    case SDLK_DOWN:
                        return 4;
                        break;
                    case SDLK_c:
                        return 5;
                    case SDLK_ESCAPE:
                        this->running = false;
                        return 6;
                    default:
                        return 0;
                }
                break;
        }
        return 0;
    }
    return 0;
}

int Game::Run(){ 
    GameData gameData;
    GameView * gameView = new GameView(this->window, this->renderer);
    MockServer * mockServer = new MockServer();
    Pause * pause = new Pause(this->window, this->renderer);
    pause->Setup(window, renderer);
    while(!this->close){           
        while(!running){
            int pausechoice = pause->showpause();
            switch (pausechoice) {
                case 0: {  
                        this->running = true;
                    break;
                }
                case 1: {  
                    std::cout << "saindo do singleplayer." << std::endl;                        
                        this->close = 1;
                        this->running = true;
                    break;
                }
                default:
                    std::cout << "Escolha inválida." << std::endl;
                    break;
            }
        }
        mockServer->update(Game::GetInput(), gameData);     
        gameData = mockServer->getState();
        gameView->Draw(gameData);
    };
    delete gameView;
    return 0;
}


