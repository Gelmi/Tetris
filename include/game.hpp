#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>

class Game {
    public:
        int Run();

    private:
        SDL_Surface* winSurface;
        SDL_Window* window;
} ;

#endif 
