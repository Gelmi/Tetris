#include "view.hpp"
#include "menu.hpp"
#include <iostream>

void Menu::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {


    this->window = sharedWindow;
    this->renderer = sharedRenderer;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "Error initializing TTF: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }



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


    // screen = SDL_GetWindowSurface(this->window);
}


// Codigo antes de alterar


// int Menu::showmenu() {
//     TTF_Font* font = TTF_OpenFont("./assets/stocky.ttf", 36);
//     if (!font) {
//         std::cout << "Error loading font: " << TTF_GetError() << std::endl;
//         return -1;
//     }

//     const int NUMMENU = 4;
//     const char* labels[NUMMENU] = {"Single Player", "Multiplayer", "Credits", "Exit"};
//     SDL_Texture* menus[NUMMENU] = {nullptr};
//     SDL_Rect pos[NUMMENU];

//     SDL_Color color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}}; // Branco e vermelho

//     // Função para recriar texturas
//     auto createMenuTextures = [&]() {
//         for (int i = 0; i < NUMMENU; ++i) {
//             if (menus[i]) {
//                 SDL_DestroyTexture(menus[i]);
//             }
//             SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], color[0]);
//             if (!surface) {
//                 std::cerr << "Erro ao criar superfície: " << TTF_GetError() << std::endl;
//                 return -1;
//             }
//             menus[i] = SDL_CreateTextureFromSurface(renderer, surface);
//             SDL_FreeSurface(surface);

//             if (!menus[i]) {
//                 std::cerr << "Erro ao criar textura: " << SDL_GetError() << std::endl;
//                 return -1;
//             }
//         }
//         return 0;
//     };

//     // Criação inicial das texturas
//     if (createMenuTextures() != 0) {
//         return -1;
//     }

//     SDL_Event event;
//     bool running = true;

//     while (running) {
//         int windowWidth, windowHeight, scaleX, scaleY;
//         SDL_GetWindowSize(this->window, &windowWidth, &windowHeight);

//         scaleX = windowWidth / 800.0f; 
//         scaleY = windowHeight / 640.0f;

//         // Calcula dinamicamente as posições dos menus
//         for (int i = 0; i < NUMMENU; ++i) {
//             int texWidth, texHeight;
//             SDL_QueryTexture(menus[i], nullptr, nullptr, &texWidth, &texHeight);
//             pos[i].x = windowWidth  / 2 - texWidth  / 2;
//             pos[i].y = windowHeight / 2 - texHeight * (2 - i) * 2 ;
//             pos[i].w = texWidth;
//             pos[i].h = texHeight;
//         }

//         // Processa eventos
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     running = false;
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:
//                     int x = event.button.x;
//                     int y = event.button.y;
//                     for (int i = 0; i < NUMMENU; ++i) {
//                         if (x >= pos[i].x  && x <= pos[i].x + pos[i].w &&
//                             y >= pos[i].y && y <= pos[i].y + pos[i].h) {
//                             for (int j = 0; j < NUMMENU; ++j) {
//                                 SDL_DestroyTexture(menus[j]);
//                             }
//                             return i;
//                         }
//                     }
//                     break;
//             }
//         }

//         // Renderiza o menu
//         SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);

//         for (int i = 0; i < NUMMENU; ++i) {
//             SDL_RenderCopy(renderer, menus[i], nullptr, &pos[i]);
//         }

//         SDL_RenderPresent(renderer);
//         SDL_Delay(16); // Limita a 60 FPS
//     }

//     // Libera recursos
//     for (int i = 0; i < NUMMENU; ++i) {
//         SDL_DestroyTexture(menus[i]);
//     }

//     return -1;
// }


// Modelo vermelho
// int Menu::showmenu() {
//     TTF_Font* font = TTF_OpenFont("./assets/stocky.ttf", 36);
//     if (!font) {
//         std::cout << "Error loading font: " << TTF_GetError() << std::endl;
//         return -1;
//     }

//     const int NUMMENU = 4;
//     const char* labels[NUMMENU] = {"Single Player", "Multiplayer", "Credits", "Exit"};
//     SDL_Texture* menus[NUMMENU] = {nullptr};
//     SDL_Rect pos[NUMMENU];

//     SDL_Color white = {255, 255, 255, 255}; // Cor branca
//     SDL_Color red = {255, 0, 0, 255};       // Cor vermelha (selecionado)

//     int selectedIndex = 0;

//     // Cria texturas iniciais
//     auto createTextures = [&](int hoverIndex) {
//         for (int i = 0; i < NUMMENU; ++i) {
//             if (menus[i]) {
//                 SDL_DestroyTexture(menus[i]);
//             }

//             SDL_Color currentColor = (i == hoverIndex) ? red : white;

//             SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], currentColor);
//             if (!surface) {
//                 std::cerr << "Erro ao criar superfície: " << TTF_GetError() << std::endl;
//                 return false;
//             }

//             menus[i] = SDL_CreateTextureFromSurface(renderer, surface);
//             pos[i].w = surface->w;
//             pos[i].h = surface->h;
//             SDL_FreeSurface(surface);

//             if (!menus[i]) {
//                 std::cerr << "Erro ao criar textura: " << SDL_GetError() << std::endl;
//                 return false;
//             }
//         }
//         return true;
//     };

//     if (!createTextures(selectedIndex)) {
//         return -1;
//     }

//     SDL_Event event;
//     bool running = true;

//     while (running) {
//         int windowWidth, windowHeight;
//         SDL_GetWindowSize(this->window, &windowWidth, &windowHeight);

//         // Calcula as posições para centralizar os itens
//         int totalHeight = 0;
//         for (int i = 0; i < NUMMENU; ++i) {
//             totalHeight += pos[i].h + 20; // Altura total com espaçamento
//         }

//         int startY = (windowHeight - totalHeight) / 2;
//         for (int i = 0; i < NUMMENU; ++i) {
//             pos[i].x = (windowWidth - pos[i].w) / 2; // Centraliza horizontalmente
//             pos[i].y = startY;
//             startY += pos[i].h + 20; // Incrementa para o próximo item
//         }

//         // Processa eventos
//         while (SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_QUIT:
//                     running = false;
//                     break;
//                 case SDL_KEYDOWN:
//                     if (event.key.keysym.sym == SDLK_DOWN) {
//                         selectedIndex = (selectedIndex + 1) % NUMMENU;
//                         createTextures(selectedIndex); // Atualiza texturas
//                     } else if (event.key.keysym.sym == SDLK_UP) {
//                         selectedIndex = (selectedIndex - 1 + NUMMENU) % NUMMENU;
//                         createTextures(selectedIndex); // Atualiza texturas
//                     } else if (event.key.keysym.sym == SDLK_RETURN) {
//                         for (int i = 0; i < NUMMENU; ++i) {
//                             SDL_DestroyTexture(menus[i]);
//                         }
//                         return selectedIndex; // Retorna o índice selecionado
//                     }
//                     break;
//                 case SDL_MOUSEBUTTONDOWN: {
//                     int x = event.button.x;
//                     int y = event.button.y;
//                     for (int i = 0; i < NUMMENU; ++i) {
//                         if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
//                             y >= pos[i].y && y <= pos[i].y + pos[i].h) {
//                             for (int j = 0; j < NUMMENU; ++j) {
//                                 SDL_DestroyTexture(menus[j]);
//                             }
//                             return i; // Retorna o índice do menu clicado
//                         }
//                     }
//                     break;
//                 }
//                 case SDL_MOUSEMOTION: {
//                     int x = event.motion.x;
//                     int y = event.motion.y;
//                     for (int i = 0; i < NUMMENU; ++i) {
//                         if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
//                             y >= pos[i].y && y <= pos[i].y + pos[i].h) {
//                             if (selectedIndex != i) {
//                                 selectedIndex = i;
//                                 createTextures(selectedIndex); // Atualiza texturas
//                             }
//                         }
//                     }
//                     break;
//                 }
//             }
//         }

//         // Renderiza o menu
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fundo preto
//         SDL_RenderClear(renderer);

//         for (int i = 0; i < NUMMENU; ++i) {
//             SDL_RenderCopy(renderer, menus[i], nullptr, &pos[i]);
//         }

//         SDL_RenderPresent(renderer);
//         SDL_Delay(16); // Limita a 60 FPS
//     }

//     // Libera recursos
//     for (int i = 0; i < NUMMENU; ++i) {
//         SDL_DestroyTexture(menus[i]);
//     }

//     return -1;
// }

// modelo parecido com credits
int Menu::showmenu() {
    SDL_Event event;
    bool running = true;

    // Configurações de texto e fontes
    TTF_Font* font = TTF_OpenFont("./assets/stocky.ttf", 36);
    if (!font) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return -1;
    }

    SDL_Color color = {255, 255, 255, 255}; // Cor branca

    const char* labels[] = {"Single Player", "Multiplayer", "Credits", "Exit"};
    SDL_Rect buttonRect[4];

    // Calcula as posições dos botões
    int windowWidth, windowHeight;
    SDL_GetWindowSize(this->window, &windowWidth, &windowHeight);
    
    for (int i = 0; i < 4; ++i) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], color);
        if (!surface) {
            std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
            return -1;
        }
        
        SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        int texWidth, texHeight;
        SDL_QueryTexture(buttonTexture, nullptr, nullptr, &texWidth, &texHeight);
        
        buttonRect[i] = {windowWidth / 2 - texWidth / 2, windowHeight / 2 - texHeight * (2 - i) * 2, texWidth, texHeight};
        
        // Renderiza o botão
        SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect[i]);
        SDL_DestroyTexture(buttonTexture);
    }

    // Loop de eventos
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Verifica clique nos botões
                for (int i = 0; i < 4; ++i) {
                    if (x >= buttonRect[i].x && x <= buttonRect[i].x + buttonRect[i].w &&
                        y >= buttonRect[i].y && y <= buttonRect[i].y + buttonRect[i].h) {
                        return i; // Retorna o índice do botão clicado
                    }
                }
            }
        }

        // Renderiza a tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fundo preto
        SDL_RenderClear(renderer);

        // Desenha os botões
        for (int i = 0; i < 4; ++i) {
            SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], color);
            if (!surface) {
                std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
                return -1;
            }
            
            SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect[i]);
            SDL_DestroyTexture(buttonTexture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limita a 60 FPS
    }

    return -1;
}





Menu::~Menu() {
    // TTF_Quit(); // Encerra a biblioteca SDL_ttf
    // SDL_Quit(); // Encerra o SDL
}
