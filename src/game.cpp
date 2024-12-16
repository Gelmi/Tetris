#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include "gameview.hpp"
#include "gamedata.hpp"
#include "mockserver.hpp"

Game::Game() {
    this->close = 0;
}

void Game::Setup() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
    }
    this->close = 0;
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

int Game::Run(){ 
    Game::Setup();
    GameData gameData;
    GameView gameView;
    MockServer mockServer = MockServer();
    while(!this->close){
        mockServer.update(Game::GetInput());     
        gameData = mockServer.getState();
        gameView.Draw(gameData);
    };
    SDL_Quit();
    return 0;
}
