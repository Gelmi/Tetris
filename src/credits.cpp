#include "credits.hpp"
#include <iostream>

void Credits::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;

    if (TTF_Init() < 0) {
        std::cerr << "Error initializing TTF: " << TTF_GetError() << std::endl;
        exit(1);
    }

    font = TTF_OpenFont("./assets/stocky.ttf", 36); // Certifique-se de que o caminho está correto
    if (!font) {
        std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
        exit(1);
    }
}

void Credits::ShowCredits() {
    SDL_Event event;
    bool running = true;

    while (running) {
        // Processa os eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Botão "Back"
                if (x >= 300 && x <= 500 && y >= 400 && y <= 450) {
                    running = false;
                }
            }
        }

        // Renderiza a tela de créditos
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fundo preto
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255, 255}; // Cor branca

        const char* lines[] = {
            "Developers:",
            "Gabriel",
            "Guilherme"
        };

        int yOffset = 200; // Posição inicial vertical
        for (int i = 0; i < 3; i++) {
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, lines[i], white);
            if (!textSurface) {
                std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
                continue;
            }
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_Rect textRect = {200, yOffset, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            // Desenhar linha abaixo do texto
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Branco
            SDL_RenderDrawLine(renderer, 200, yOffset + textRect.h + 5, 600, yOffset + textRect.h + 5);

            yOffset += textRect.h + 20; // Incrementa a posição para o próximo texto
        }

        // Botão "Back"
        SDL_Surface* backSurface = TTF_RenderText_Solid(font, "Back", white);
        SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);

        SDL_Rect backRect = {300, 400, backSurface->w, backSurface->h};
        SDL_RenderCopy(renderer, backTexture, nullptr, &backRect);

        SDL_FreeSurface(backSurface);
        SDL_DestroyTexture(backTexture);

        SDL_RenderPresent(renderer);
    }
}

Credits::~Credits() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    //     TTF_Quit(); // Encerra a biblioteca SDL_ttf
    // SDL_Quit(); // Encerra o SDL
}
