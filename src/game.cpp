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
    if(!window) std::cerr << "Game Didnt Receive Window" << SDL_GetError() << std::endl;
    if(!renderer) std::cerr << "Game Didnt Receive Renderer" << SDL_GetError() << std::endl;
}

Game::~Game() {
    if (this->renderer) SDL_DestroyRenderer(this->renderer);
    if (this->window) SDL_DestroyWindow(this->window);
    SDL_Quit();
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
                    case SDLK_c:
                        return 5;
                    case SDLK_ESCAPE:
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
    while(!this->close){

        // std::cout << "Window resized: " << windowWidth << "x" << windowHeight << std::endl;
        if (Game::GetInput() == 6){

            bool runningpause = true;

            Pause * pause = new Pause(this->window, this->renderer);
            pause->Setup(window, renderer);
            while(runningpause){
                int pausechoice = pause->showpause();
                switch (pausechoice) {
                    case 0: {  
                            runningpause = false;
                        break;
                    }
                    case 1: { 
                        std::cout << "saindo do singleplayer." << std::endl;                        
                            Application app;
                            app.Run();
                        break;
                    }
                    default:
                        std::cout << "Escolha inválida." << std::endl;
                        break;
                }
            }
        }
        mockServer->update(Game::GetInput(), gameData);     
        gameData = mockServer->getState();
        gameView->Draw(gameData);
    };
    return 0;
}


