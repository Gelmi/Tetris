/**
 * @file server_main.cpp
 * @author Gabriel and Corsi
 * @brief This files handles the Servidor main looping 
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "server.hpp"
#include <enet/enet.h>
#include <iostream>

int main() {
    if(enet_initialize() != 0) {
        std::cerr << "An error occured while initializing Enet.\n";
    }
    Server * server = new Server();
    return server->Run();
}
