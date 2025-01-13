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

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating window (Application): " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

Application::~Application() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Application::GetWindow() const {
    return window;
}

SDL_Renderer* Application::GetRenderer() const {
    return renderer;
}

void Application::Run(){

 bool running = true;

    // Criação dos objetos fora do loop
    Menu menu(window, renderer);
    Credits credits(window, renderer);

    // Loop principal de navegação entre telas
    while (running) {
        menu.Setup(window, renderer);
        credits.Setup(window, renderer);

        int menuChoice = menu.showmenu();

        switch (menuChoice) {
            case 0: { // Jogo Single Player
                Game game(window, renderer);
                game.Run();
                break;
            }
            case 1: { // Placeholder para Multiplayer
                std::cout << "Multiplayer ainda não implementado." << std::endl;
                break;
            }
            case 2: { // Créditos
                credits.ShowCredits();
                // Retornar ao menu após os créditos
                break;
            }
            case 3: { // Sair
                std::cout << "Exiting the game. Goodbye!" << std::endl;
                running = false;
                break;
            }
            default:
                std::cout << "Escolha inválida." << std::endl;
                break;
        }
    }
}

