#include "view.hpp"
#include "menu.hpp"
#include <iostream>

void Menu::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "Error initializing TTF: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    this->window = sharedWindow;
    this->renderer = sharedRenderer;

    if (!this->window) {
        std::cout << "Error creating window (menu): " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    if (!this->renderer) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    // Configura a cor padrão do renderer
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);

    screen = SDL_GetWindowSurface(this->window);
}


int Menu::showmenu() {

    TTF_Font* font = TTF_OpenFont("./assets/stocky.ttf", 36);
    if (!font) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return -1;
    }

    Uint32 time;
    int x, y;
    const int NUMMENU = 4;
    const char* labels[NUMMENU] = {"Single Player", "Multiplayer", "Credits", "Exit"};
    SDL_Surface* menus[NUMMENU];
    // bool selected[NUMMENU] = {0, 0};
    SDL_Color color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};

    menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]); // Game
    menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]); // Multiplayer
    menus[2] = TTF_RenderText_Solid(font, labels[2], color[0]); // Multiplayer
    menus[3] = TTF_RenderText_Solid(font, labels[3], color[0]); // Exit


    SDL_Rect pos[NUMMENU];
    for (int i = 0; i < NUMMENU; ++i) {
        pos[i].x = screen->clip_rect.w / 2 - menus[i]->clip_rect.w / 2;
        pos[i].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h * (2 - i) * 2;
    }


    SDL_Event event;

    while (true) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_FreeSurface(menus[0]);
                    SDL_FreeSurface(menus[1]);
                    SDL_FreeSurface(menus[2]);
                    SDL_FreeSurface(menus[3]);
                    return 3;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for (int i = 0; i < NUMMENU; i++) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            SDL_FreeSurface(menus[0]);
                            SDL_FreeSurface(menus[1]);
                            SDL_FreeSurface(menus[2]);
                            SDL_FreeSurface(menus[3]);
                            return i;
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        for (int i = 0; i < NUMMENU; i++) {
            SDL_BlitSurface(menus[i], nullptr, screen, &pos[i]);
        }
        SDL_UpdateWindowSurface(this->window);

        if (1000 / 30 > (SDL_GetTicks() - time)) {
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
        }
    }

}


Menu::~Menu() {
    // if (window) {
    //     SDL_DestroyWindow(window); // Destroi a janela criada
    // }
    TTF_Quit(); // Encerra a biblioteca SDL_ttf
    SDL_Quit(); // Encerra o SDL
}
