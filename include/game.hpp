#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>

class Game {
    public:
        int Run();
        void Setup();
        int GetInput();
        Game();

    private:
        int close{0};
} ;

#endif 
