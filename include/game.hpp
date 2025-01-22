#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>
#include "view.hpp"

class Game : public View {
    public:
        int Run();
        void Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer, float scaleX, float scaleY);
        int GetInput();
        Game(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer, float scaleX, float scaleY) 
        : View(sharedWindow, sharedRenderer), close(false), scaleX(scaleX), scaleY(scaleY) {}

        // std::cout << "Construtor chamado: scaleX = " << scaleX << ", scaleY = " << scaleY << std::endl;

    private:
        int close{0};
        SDL_Window* window;      
        SDL_Renderer* renderer;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
} ;

#endif 
