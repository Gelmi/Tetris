#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include "gameview.hpp"
#include "gamedata.hpp"

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

void Game::GetInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                this->close = 1;
                break;
        }
    }
}

int Game::Run(){ 
    Game::Setup();
    GameData gameData;
    GameView gameView;
    gameData.x = 32;
    gameData.y = 32;
    while(!this->close){
        Game::GetInput();     
        gameView.Draw(gameData);
    };
    SDL_Quit();
    return 0;
}
