// #include "gameview.hpp"
// #include "menu.hpp"
// #include "game.hpp"
// #include <iostream>

// int main() {

//     Menu menu;
//     menu.Setup(); // Configuração inicial do menu

//     int menuChoice = menu.showmenu(); // Exibir o menu e capturar a escolha do usuário

//     if (menuChoice == 0) {
//         Game game;
//         return game.Run(); // Inicia o jogo no modo normal
//     } else if (menuChoice == 1) {
//         // MultiplayerGame multiplayerGame;
//         Game game;
//         return game.Run(); // Inicia o jogo no modo multiplayer
//     } else {
//         std::cout << "Exiting the game. Goodbye!" << std::endl;
//         return 0; // Sai do programa
//     }
// }


#include "application.hpp"
#include "menu.hpp"
#include "game.hpp"
#include <iostream>

int main() {
    Application app; // Criação do contexto da aplicação

    // Exibe o menu
    Menu menu(app.GetWindow(), app.GetRenderer());
    menu.Setup(app.GetWindow(), app.GetRenderer()); // Configuração inicial do menu
    int menuChoice = menu.showmenu(); // Exibir o menu e capturar a escolha do usuário

    // Decisão com base na escolha do menu
    if (menuChoice == 0) {
        Game game(app.GetWindow(), app.GetRenderer());
        return game.Run(); // Roda o jogo no modo normal
    } else if (menuChoice == 1) {
        // Aqui você pode implementar o jogo multiplayer no futuro
        std::cout << "Multiplayer ainda não implementado." << std::endl;
        return 0;
    } else {
        std::cout << "Exiting the game. Goodbye!" << std::endl;
        return 0;
    }
}


