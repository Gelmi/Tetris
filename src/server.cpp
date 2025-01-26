/**
 * @file server.cpp
 * @author Gabriel et Guilherme
 * @brief Ce fichier mis en place le serveur
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <enet/enet.h>

int main() {
    ENetAddress address;
    ENetHost *server;
    ENetEvent event;
    int eventStatus;

    //Initialize Enet
    if(enet_initialize() != 0) {
        std::cerr << "An error occured while initializing Enet.\n";
        return EXIT_FAILURE;
    }

    atexit(enet_deinitialize);

    address.host = ENET_HOST_ANY;
    address.port = 1234;

    server = enet_host_create(&address, 32, 2, 0, 0);

    if(server == NULL) {
        std::cerr << "An error occured while trying to create an ENet server host\n";
        exit(EXIT_FAILURE);
    }

    while(1) {
        eventStatus = enet_host_service(server, &event, 50000);

        if(eventStatus > 0) {
            switch(event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    std::cout << "(Server) We got a new connection from " << event.peer->address.host << "\n";
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    std::cout << "(Server) Message from client : " << event.packet->data << "\n";
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << "(Server) " << event.peer->data << " disconnected\n";
                    event.peer->data = NULL;
                    break;
            }
        }
    }
    return 1;
}
