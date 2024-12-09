#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include "board.hpp"
#include "tetromino.hpp"

int Game::Run(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);
    if(!window){
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if ( !renderer ) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}
    Board board(renderer);
    SDL_Color vermeio;
    vermeio.r = 255;
    vermeio.g = 0;
    vermeio.b = 0;
    vermeio.a = 255;
    unsigned int shape[16] =  {0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0};
    Tetromino tetromino(renderer, vermeio, shape);
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
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	    SDL_RenderClear( renderer );
        board.Draw();
        tetromino.Draw();
        SDL_RenderPresent( renderer );
    };
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
