/**
 * @file application.cpp
 * @author Gabriel et Guilherme
 * @brief Ce fichier démarre le boucle principal
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "application.hpp"
#include "menu.hpp"
#include "game.hpp"
#include "credits.hpp"
#include <iostream>

Application::Application() : window(nullptr), renderer(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating window (Application): " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, 800, 640);
}

Application::~Application() {
    if (this->renderer) SDL_DestroyRenderer(this->renderer);
    if (this->window) SDL_DestroyWindow(this->window);
    SDL_Quit();
}

SDL_Window* Application::GetWindow() const {
    return this->window;
}

SDL_Renderer* Application::GetRenderer() const {
    return this->renderer;
}

/**
 * @brief Cette fonction est la boucle principal de navegation parmi des écrans
 * 
 * @return int 
 */
int Application::Run(){

 bool running = true;
    /// Creation des objects dehors la boucle
    Menu * menu = new Menu(this->window, this->renderer);
    Credits * credits = new Credits(this->window, this->renderer);

    menu->Setup(window, renderer);
    credits->Setup(window, renderer);

    while (running) {
        int menuChoice = menu->showmenu();


        switch (menuChoice) {
            case 0: {/// Game
                Game * game = new Game(this->window, this->renderer);
                game->Setup(window, renderer);
                game->Run();
                break;
            }
            case 1: { /// Multiplayer
                std::cout << "Multiplayer ainda não implementado." << std::endl;
                break;
            }
            case 2: { /// Credits
                credits->ShowCredits();

                break;
            }
            case 3: { ///  Sortir
                std::cout << "Exiting the game. Goodbye!" << std::endl;
                running = false;
                break;
            }
            default:
                std::cout << "Escolha inválida. AAA" << std::endl;
                break;
        }
    

    }

    // Nettoyage final
    delete menu;
    delete credits;

    return 0;
}

