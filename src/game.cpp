#include "game.hpp"
#include <SDL.h>
#include <iostream>

int Game::Run(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 1280, SDL_WINDOW_SHOWN);
    if(!window){
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    winSurface = SDL_GetWindowSurface(window);
    if(!winSurface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
    SDL_UpdateWindowSurface(window);
    int close = 0;
    while(!close){
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
            }
        }
    };
    SDL_FreeSurface(winSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
