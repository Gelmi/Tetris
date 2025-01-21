#ifndef MULTIPLAYER_HPP
#define MULTIPLAYER_HPP

#include <SDL.h>
#include "view.hpp"

class Multiplayer : public View {
    public:
        Multiplayer(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer)
            : View(sharedWindow, sharedRenderer) {};

        void Setup(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer);
        int Run();

    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
};

#endif
