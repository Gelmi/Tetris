#include "application.hpp"
#include "menu.hpp"
#include "game.hpp"
#include "credits.hpp"
#include <iostream>
#include "multiplayer.hpp"
#include <memory>

Application::Application() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "Error initializing TTF: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }   

    this->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating window (Application): " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
}

Application::~Application() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

SDL_Window* Application::GetWindow() const {
    return this->window;
}

SDL_Renderer* Application::GetRenderer() const {
    return this->renderer;
}

int Application::Run(char * ip){

 bool running = true;

    // Criação dos objetos fora do loop
    std::unique_ptr<Menu> menu = std::make_unique<Menu>(this->window, this->renderer);
    std::unique_ptr<Credits> credits = std::make_unique<Credits>(this->window, this->renderer);

    // Loop principal de navegação entre telas
    menu->Setup(window, renderer);
    credits->Setup(window, renderer);

    while (running) {
        int menuChoice = menu->showmenu();

        switch (menuChoice) {
            case 0: { // Jogo Single Player    
                std::unique_ptr<Game> game = std::make_unique<Game>(this->window, this->renderer);
                game->Setup(window, renderer);
                game->Run();
                break;
            }
            case 1: { // Placeholder para Multiplayer 
                std::unique_ptr<Multiplayer> multiplayer = std::make_unique<Multiplayer>(this->window, this->renderer);
                multiplayer->Setup(window, renderer);
                multiplayer->Run(ip);
                break;
            }
            case 2: { // Créditos
                credits->ShowCredits();
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
    return 0;
}

