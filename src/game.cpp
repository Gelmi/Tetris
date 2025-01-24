#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include "gameview.hpp"
#include "gamedata.hpp"
#include "mockserver.hpp"
#include "constants.hpp"

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
        mockServer->update(Game::GetInput(), gameData);     
        gameData = mockServer->getState();
        gameView->Draw(gameData);
    };
    return 0;
}
