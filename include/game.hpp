#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>

class Game : public View {
    public:
        int Run();
        void Setup();
        int GetInput();
        Game(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer)
        : View(sharedWindow, sharedRenderer), close(false) {}

    private:
        int close{0};
        SDL_Window* window;       // Janela principal
        SDL_Renderer* renderer; 
} ;

#endif 
