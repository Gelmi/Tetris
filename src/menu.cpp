/**
 * @file menu.cpp
 * @author Gabriel and Guilherme
 * @brief This file handles the menu scren
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "view.hpp"
#include "menu.hpp"
#include <iostream>

/**
 * @brief Construct a new Menu:: Menu object
 * 
 * @param sharedWindow 
 * @param sharedRenderer 
 */
void Menu::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;

    // Configura a cor padrão do renderer
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);

    this->screen = SDL_GetWindowSurface(this->window);

    this->font = TTF_OpenFont("./assets/stocky.ttf", 36);
    
    if (!font) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
    }

    this->fontTitle = TTF_OpenFont("./assets/stocky.ttf", 60);
}

/**
 * @brief Destroy the Menu:: Menu object
 * 
 */
Menu::~Menu() {
    if (font) TTF_CloseFont(font);
}

/**
 * @brief This function is responsable for build the layout and return the menu choice
 * 
 * @return int 
 */
int Menu::showmenu() {
    Uint32 time;
    int x, y;
    const int NUMMENU = 5;
    const char* labels[NUMMENU] = {"Tetris", "Single Player", "Multiplayer", "Credits", "Exit"};
    SDL_Color color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};

    int windowWidth = 800, windowHeight = 640;


/// @brief This loop creates the proportional place for the options
    SDL_Rect pos[NUMMENU];
    for (int i = 0; i < NUMMENU; ++i) {
        SDL_Surface * surface;
        if(i == 0) surface = TTF_RenderText_Solid(fontTitle, labels[i], color[0]);
        else surface = TTF_RenderText_Solid(font, labels[i], color[0]);
        SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
        int texWidth, texHeight;
        SDL_QueryTexture(buttonTexture, nullptr, nullptr, &texWidth, &texHeight);
        if(i == 0) pos[i] = {windowWidth / 2 - (texWidth*1.2) / 2, windowHeight / 2 - (texHeight) * (1.5 - i) * 2, texWidth*1.2, texHeight*1.2};
        else pos[i] = {windowWidth / 2 - texWidth / 2, windowHeight / 2 - texHeight * (2 - i) * 2, texWidth, texHeight};
        SDL_FreeSurface(surface);
    }

    SDL_Event event;

/// @brief This loop deals with the events in the buttons 
    while (true) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return 3;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for (int i = 1; i < NUMMENU; i++) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            return i-1;
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUMMENU; i++) {
             SDL_Surface * surface;
            if(i == 0) surface = TTF_RenderText_Solid(fontTitle, labels[i], color[0]);
            else surface = TTF_RenderText_Solid(font, labels[i], color[0]);

            if(!surface) {
                std::cerr << "Error creating surface: " << TTF_GetError() << std::endl;
                return -1;
            }
            SDL_Texture * buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, buttonTexture, nullptr, &pos[i]);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(buttonTexture);
        }
        
        SDL_RenderPresent(renderer);

        if (1000 / 30 > (SDL_GetTicks() - time)) {
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
        }
    }

}
