#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>
#include "view.hpp"

class Game : public View {
    public:
        int Run();
        void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer);
        int GetInput();
        Game(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) 
        : View(sharedWindow, sharedRenderer), close(false), running(true), lose(false) {}
        void PauseMenu();
        void gameEndMenu();

    private:
        bool close{false};
        int running{true};
        bool lose{false};
        SDL_Window* window;       // Janela principal
        SDL_Renderer* renderer;
} ;

#endif 
