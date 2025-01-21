#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include "gameview.hpp"
#include "gamedata.hpp"
#include "mockserver.hpp"
#include "application.hpp"

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
    while(!this->close){
        mockServer->update(Game::GetInput());     
        gameData = mockServer->getState();
        gameView->Draw(gameData);
    };
    SDL_Quit();
    return 0;
}
