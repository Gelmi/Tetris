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

int Application::Run(){

 bool running = true;
//  bool fullscreen = false;

    // SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    // scaleX = windowWidth / 800.0f; 
    // scaleY = windowHeight / 640.0f; 


    // Criação dos objetos fora do loop
    Menu * menu = new Menu(this->window, this->renderer);
    Credits * credits = new Credits(this->window, this->renderer);
    // Loop principal de navegação entre telas
    menu->Setup(window, renderer);
    credits->Setup(window, renderer);

    while (running) {
        int menuChoice = menu->showmenu();

        switch (menuChoice) {
            case 0: { // Jogo Single Player  
                Game * game = new Game(this->window, this->renderer);
                game->Setup(window, renderer);
                game->Run();
                delete game;
                break;
            }
            case 1: { // Placeholder para Multiplayer
                std::cout << "Multiplayer ainda não implementado." << std::endl;
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

    // Limpeza final
    delete menu;
    delete credits;

    return 0;
}

