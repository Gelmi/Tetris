#include "multiplayer.hpp"
#include <enet/enet.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "constants.hpp"
#include "multigameview.hpp"

Multiplayer::~Multiplayer() {
    enet_deinitialize();
}

void Multiplayer::Setup(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;
    this->running = true;
    this->connected = false;
    this->gameData = new GameData();
}

int Multiplayer::connect() {
    if(enet_initialize() != 0) {
        fprintf(stderr, "An error occured while initializing ENet\n");
        return EXIT_FAILURE;
    }

    client = enet_host_create(NULL, 1, 2, 0, 0);

    if(client==NULL){
        fprintf(stderr, "An error occured while trying to create an ENet server host\n");
        return EXIT_FAILURE;
    } 
 
    enet_address_set_host(&address, "localhost");
    address.port = 1234;

    peer = enet_host_connect(client, &address, 2, 0);

    if(peer == NULL) {
        fprintf(stderr, "No available peers for initializing an ENet connection");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Multiplayer::pollSDLEvent(ENetPeer * peer) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch(sdlEvent.type) {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_KEYDOWN:
                ClientData clientData;
                clientData.messageType = 12;
                switch(sdlEvent.key.keysym.sym){
                    case SDLK_SPACE: {
                        clientData.m1 = SPACE_BAR;
                        break;
                    }
                    case SDLK_UP: {
                        clientData.m1 = ARROW_UP;
                        break;
                    }
                    case SDLK_DOWN: {
                        clientData.m1 = ARROW_DOWN;
                        break;
                    }
                    case SDLK_LEFT: {
                        clientData.m1 = ARROW_LEFT;
                        break;
                    }
                    case SDLK_RIGHT: {
                        clientData.m1 = ARROW_RIGHT;
                        break;
                    }

                }
                printf("Enviando pacote\n");
                ENetPacket *packet = enet_packet_create(&clientData, sizeof(clientData), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(peer, 0, packet);
        }
    }
}

void Multiplayer::handleServer() {
    eventStatus = enet_host_service(client, &event, 0);

    if(eventStatus>0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                printf("(Client) We got a new connection from %x\n",
                        event.peer->address.host);
                this->connected = true;
                break; 
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                ClientData * clientData = reinterpret_cast<ClientData*>(event.packet->data);
                if(clientData->messageType == COMMAND_MESSAGE) printf("(Client) Message from server : %d\n", clientData->m1);
                if(clientData->messageType == CONNECT_MESSAGE) {
                    printf("(Client) Your clientID is: %u\n", clientData->m2);
                    this->connectID = clientData->m2;
                }
                if(clientData->messageType == STATE_MESSAGE) {
                    printf("Board:");
                    for(int i = 0; i < 200; i++) {
                        printf(" %d", clientData->m4[i]);
                    }
                    printf("\n");
                    Multiplayer::clientToGame(clientData);
                }
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: {
                printf("(Client) %s disconnected.\n", event.peer->data);

                event.peer->data = NULL;
                this->connected = false;
                break;
            }
        }
    }
}

void Multiplayer::clientToGame(ClientData * clientData){
    this->gameData->score = 0;
    this->gameData->level = 0;
    this->gameData->rows = 0;
    if(connectID == clientData->m2) {
        for(int i = 0; i < 200; i++) {
            this->gameData->board[i] = clientData->m4[i];
            this->gameData->boardOp[i] = clientData->m5[i];
        } 
    } else {
        for(int i = 0; i < 200; i++) {
            this->gameData->board[i] = clientData->m5[i];
            this->gameData->boardOp[i] = clientData->m4[i];
        }
    }
    for(int i = 0; i < 16; i++) this->gameData->tiles[i] = 0;
}

int Multiplayer::Run() {  
   
    MultiGameView * gameView = new MultiGameView(this->window, this->renderer);


    if(Multiplayer::connect() == EXIT_FAILURE) return 0;

    while(this->running) {  
        Multiplayer::pollSDLEvent(peer);
        Multiplayer::handleServer();
        if(connected) {
            gameView->Draw(*(this->gameData));
            gameView->DrawBoardOp(*(this->gameData));
        }
    }
}
