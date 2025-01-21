#include "multiplayer.hpp"
#include <enet/enet.h>
#include <stdio.h>
#include <string.h>

void Multiplayer::Setup(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;
}

int Multiplayer::Run() {
    ENetAddress address;
    ENetHost *client;
    ENetPeer * peer;
    char message[1024];
    ENetEvent event;
    int eventStatus;
    if(enet_initialize() != 0) {
        fprintf(stderr, "An error occured while initializing ENet\n");
        return EXIT_FAILURE;
    }

    atexit(enet_deinitialize);

    client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);

    if(client==NULL){
        fprintf(stderr, "An error occured while trying to create an ENet server host\n");
        exit(EXIT_FAILURE);
    }

    enet_address_set_host(&address, "localhost");
    address.port = 1234;

    peer = enet_host_connect(client, &address, 2, 0);

    if(peer == NULL) {
        fprintf(stderr, "No available peers for initializing an ENet connection");
        exit(EXIT_FAILURE);
    }

    SDL_Event sdlEvent;
    bool running = true;
    while(running) {
        while (SDL_PollEvent(&sdlEvent)) {
            switch(sdlEvent.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(sdlEvent.key.keysym.sym){
                        case SDLK_SPACE:
                            ENetPacket *packet = enet_packet_create("Teste", strlen("Teste") + 1, ENET_PACKET_FLAG_RELIABLE);
                            enet_peer_send(peer, 0, packet);
                            break;
                    }
            }
        }

        eventStatus = enet_host_service(client, &event, 500);

        if(eventStatus>0) {
            switch(event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("(Client) We got a new connection from %x\n",
                            event.peer->address.host);
                    break;

                case ENET_EVENT_TYPE_RECEIVE:
                    printf("(Client) Message from server : %s\n", event.packet->data);
                    // Lets broadcast this message to all
                    // enet_host_broadcast(client, 0, event.packet);
                    enet_packet_destroy(event.packet);
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("(Client) %s disconnected.\n", event.peer->data);

                    // Reset client's information
                    event.peer->data = NULL;
                    break;
            }
        }
    }
}
