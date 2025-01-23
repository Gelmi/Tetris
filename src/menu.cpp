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


// Codigo antes de alterar

// int Menu::showmenu() {

//     TTF_Font* font = TTF_OpenFont("./assets/stocky.ttf", 36);
//     if (!font) {
//         std::cout << "Error loading font: " << TTF_GetError() << std::endl;
//         return -1;
//     }

//     Uint32 time;
//     int x, y;
//     const int NUMMENU = 4;
//     const char* labels[NUMMENU] = {"Single Player", "Multiplayer", "Credits", "Exit"};
//     SDL_Surface* menus[NUMMENU];
//     // bool selected[NUMMENU] = {0, 0};
//     SDL_Color color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};

//     menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]); // Game
//     menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]); // Multiplayer
//     menus[2] = TTF_RenderText_Solid(font, labels[2], color[0]); // Multiplayer
//     menus[3] = TTF_RenderText_Solid(font, labels[3], color[0]); // Exit


//     SDL_Rect pos[NUMMENU];
//     for (int i = 0; i < NUMMENU; ++i) {
//         pos[i].x = screen->clip_rect.w / 2 - menus[i]->clip_rect.w / 2;
//         pos[i].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h * (2 - i) * 2;
//     }


//     SDL_Event event;

//     while (true) {
//         time = SDL_GetTicks();
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     SDL_FreeSurface(menus[0]);
//                     SDL_FreeSurface(menus[1]);
//                     SDL_FreeSurface(menus[2]);
//                     SDL_FreeSurface(menus[3]);
//                     return 3;
//                 case SDL_MOUSEBUTTONDOWN:
//                     x = event.button.x;
//                     y = event.button.y;
//                     for (int i = 0; i < NUMMENU; i++) {
//                         if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
//                             SDL_FreeSurface(menus[0]);
//                             SDL_FreeSurface(menus[1]);
//                             SDL_FreeSurface(menus[2]);
//                             SDL_FreeSurface(menus[3]);
//                             return i;
//                         }
//                     }
//                     break;
//             }
//         }

//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);


//         for (int i = 0; i < NUMMENU; i++) {
//             SDL_BlitSurface(menus[i], nullptr, screen, &pos[i]);
//         }
//         SDL_UpdateWindowSurface(this->window);

//         if (1000 / 30 > (SDL_GetTicks() - time)) {
//             SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
//         }
//     }

// }


int Menu::showmenu() {
    TTF_Font* font = TTF_OpenFont("./assets/stocky.ttf", 36);
    if (!font) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return -1;
    }

    const int NUMMENU = 4;
    const char* labels[NUMMENU] = {"Single Player", "Multiplayer", "Credits", "Exit"};
    SDL_Texture* menus[NUMMENU] = {nullptr};
    SDL_Rect pos[NUMMENU];

    SDL_Color color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}}; // Branco e vermelho

    // Função para recriar texturas
    auto createMenuTextures = [&]() {
        for (int i = 0; i < NUMMENU; ++i) {
            if (menus[i]) {
                SDL_DestroyTexture(menus[i]);
            }
            SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], color[0]);
            if (!surface) {
                std::cerr << "Erro ao criar superfície: " << TTF_GetError() << std::endl;
                return -1;
            }
            menus[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            if (!menus[i]) {
                std::cerr << "Erro ao criar textura: " << SDL_GetError() << std::endl;
                return -1;
            }
        }
        return 0;
    };

    // Criação inicial das texturas
    if (createMenuTextures() != 0) {
        return -1;
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(this->window, &windowWidth, &windowHeight);

        // Calcula dinamicamente as posições dos menus
        for (int i = 0; i < NUMMENU; ++i) {
            int texWidth, texHeight;
            SDL_QueryTexture(menus[i], nullptr, nullptr, &texWidth, &texHeight);
            pos[i].x = windowWidth / 2 - texWidth / 2;
            pos[i].y = windowHeight / 2 - texHeight * (2 - i) * 2;
            pos[i].w = texWidth;
            pos[i].h = texHeight;
        }

        // Processa eventos
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        // Recria texturas após redimensionamento
                        if (createMenuTextures() != 0) {
                            running = false;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int x = event.button.x;
                    int y = event.button.y;
                    for (int i = 0; i < NUMMENU; ++i) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                            y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            for (int j = 0; j < NUMMENU; ++j) {
                                SDL_DestroyTexture(menus[j]);
                            }
                            return i;
                        }
                    }
                    break;
            }
        }

        // Renderiza o menu
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUMMENU; ++i) {
            SDL_RenderCopy(renderer, menus[i], nullptr, &pos[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limita a 60 FPS
    }

    // Libera recursos
    for (int i = 0; i < NUMMENU; ++i) {
        SDL_DestroyTexture(menus[i]);
    }

    return -1;
}





Menu::~Menu() {
    TTF_Quit(); // Encerra a biblioteca SDL_ttf
    SDL_Quit(); // Encerra o SDL
}
