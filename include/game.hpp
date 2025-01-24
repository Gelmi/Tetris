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
        : View(sharedWindow, sharedRenderer), close(false) {}
        ~Game();

        // std::cout << "Construtor chamado: scaleX = " << scaleX << ", scaleY = " << scaleY << std::endl;

    private:
        int close{0};
        SDL_Window* window;      
        SDL_Renderer* renderer;

} ;

#endif 
