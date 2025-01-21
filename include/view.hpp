#ifndef VIEW_HPP
#define VIEW_HPP

#include <SDL.h>

class View {
protected:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    View(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
        window = sharedWindow;
        renderer = sharedRenderer;
    }

    virtual ~View() {}

    // virtual void HandleEvent(const SDL_Event& event) = 0; // Processa eventos
    // virtual void Render() = 0;                            // Renderiza a tela
};

#endif
