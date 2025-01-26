/**
 * @file credits.cpp
 * @author Gabriel and Guilherme 
 * @brief This file handles the credits screen
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "credits.hpp"
#include <iostream>

/**
 * @brief Construct a new Credits:: Credits object
 * 
 * @param sharedWindow 
 * @param sharedRenderer 
 */
void Credits::Setup(SDL_Window* sharedWindow, SDL_Renderer* sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;

    font = TTF_OpenFont("./assets/stocky.ttf", 36); 
    if (!font) {
        std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
        exit(1);
    }
}

/**
 * @brief The main fonction to configure the text and back button
 * 
 */
void Credits::ShowCredits() {
    SDL_Event event;
    bool running = true;

    while (running) {
        /// Process the events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // button "Back"
                if (x >= 300 && x <= 500 && y >= 400 && y <= 450) {
                    running = false;
                }
            }
        }

        /// Renders the credits screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background color
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255, 255}; // white background color

        const char* lines[] = {
            "Developers:",
            "Gabriel",
            "Guilherme"
        };

        int yOffset = 200; // Vertical initial position
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

            /// Draws the line under the text  
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, 200, yOffset + textRect.h + 5, 600, yOffset + textRect.h + 5);

            yOffset += textRect.h + 20; // Add position for the next text
        }

        // Button "Back"
        SDL_Surface* backSurface = TTF_RenderText_Solid(font, "Back", white);
        SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);

        SDL_Rect backRect = {300, 400, backSurface->w, backSurface->h};
        SDL_RenderCopy(renderer, backTexture, nullptr, &backRect);

        SDL_FreeSurface(backSurface);
        SDL_DestroyTexture(backTexture);

        SDL_RenderPresent(renderer);
    }
}

/**
 * @brief Destroy the Credits:: Credits object
 * 
 */
Credits::~Credits() {
    if (font) TTF_CloseFont(font);
}
