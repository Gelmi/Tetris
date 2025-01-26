/**
 * @file pause.cpp
 * @author Gabriel and Guilherme
 * @brief This file handles the pause screen
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "view.hpp"
#include "pause.hpp"
#include <iostream>

/**
 * @brief Construct a new Pause:: Pause object
 * 
 * @param sharedWindow 
 * @param sharedRenderer 
 */
void Pause::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;
    // Configura a cor padrão do renderer
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}

/**
 * @brief The main fonction to configure the text and the continue and menu buttons
 * 
 * @return int 
 */
int Pause::showpause() {
    font = TTF_OpenFont("./assets/stocky.ttf", 36);
    if (!font) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return -1;
    }

    const int NUMMENU = 2;
    const char* labels[NUMMENU] = {"Continue", "Menu"};
    SDL_Texture* menus[NUMMENU] = {nullptr};
    SDL_Rect pos[NUMMENU];

    SDL_Color color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}}; 

    /// Function to create the textures
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

    /// First creartion of the textures
    if (createMenuTextures() != 0) {
        return -1;
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        int windowWidth = 800, windowHeight = 640;

        // Dynamically calculates menu positions
        for (int i = 0; i < NUMMENU; ++i) {
            int texWidth, texHeight;
            SDL_QueryTexture(menus[i], nullptr, nullptr, &texWidth, &texHeight);
            pos[i].x = windowWidth / 2 - texWidth / 2;
            pos[i].y = windowHeight / 2 - texHeight * (2 - i) * 2;
            pos[i].w = texWidth;
            pos[i].h = texHeight;
        }

        // Process events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        // Resizign after recreate textures 
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

        // Renders  the screen
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUMMENU; ++i) {
            SDL_RenderCopy(renderer, menus[i], nullptr, &pos[i]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limits to 60 FPS
    }

    // Drop of the resources
    for (int i = 0; i < NUMMENU; ++i) {
        SDL_DestroyTexture(menus[i]);
    }

    return false;
}
