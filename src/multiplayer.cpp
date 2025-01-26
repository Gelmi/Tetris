#include "multiplayer.hpp"
#include <enet/enet.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "constants.hpp"
#include "multigameview.hpp"
#include "tetromino.hpp"
#include "gameend.hpp"
#include <string>
#include <memory>

Multiplayer::~Multiplayer() {
    enet_deinitialize();
    delete this->gameData;
    delete this->client;
    delete this->peer;
}

void Multiplayer::Setup(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer) {
    this->window = sharedWindow;
    this->renderer = sharedRenderer;
    this->running = false;
    this->connected = false;
    this->close = false;
    this->gameData = new GameData();
    this->results = false;
}

int Multiplayer::connect(char * ip) {
    if(enet_initialize() != 0) {
        fprintf(stderr, "An error occured while initializing ENet\n");
        return EXIT_FAILURE;
    }

    client = enet_host_create(NULL, 1, 2, 0, 0);

    if(client==NULL){
        fprintf(stderr, "An error occured while trying to create an ENet server host\n");
        return EXIT_FAILURE;
    } 
    printf("ip: %s\n", ip);
    enet_address_set_host(&address, ip);
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
                this->close = true;
                break;
            case SDL_KEYDOWN:
                ClientData clientData;
                clientData.messageType = 12;
                switch(sdlEvent.key.keysym.sym){
                    case SDLK_SPACE:
                        clientData.m1 = SPACE_BAR;
                        break;
                    case SDLK_UP:
                        clientData.m1 = ARROW_UP;
                        break;
                    case SDLK_DOWN:
                        clientData.m1 = ARROW_DOWN;
                        break;
                    case SDLK_LEFT:
                        clientData.m1 = ARROW_LEFT;
                        break;
                    case SDLK_RIGHT:
                        clientData.m1 = ARROW_RIGHT;
                        break;
                    case SDLK_c:
                        clientData.m1 = SWAP;
                        break;

                }
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
                printf("Recebi pacote do tipo: %d\n", clientData->messageType);
                if(clientData->messageType == COMMAND_MESSAGE) printf("(Client) Message from server : %d\n", clientData->m1);
                if(clientData->messageType == CONNECT_MESSAGE) {
                    printf("(Client) Your clientID is: %u\n", clientData->m2);
                    this->connectID = clientData->m2;
                }
                if(clientData->messageType == START_MESSAGE) this->running = true;
                if(clientData->messageType == STATE_MESSAGE) {
                    Multiplayer::clientToGame(clientData);
                }
                if(clientData->messageType == WIN_MESSAGE) printf("Ganhei\n");
                if(clientData->messageType == LOSE_MESSAGE) printf("Perdi\n");
                if(clientData->messageType == RESULTS_MESSAGE) {
                    this->results = true;
                    Multiplayer::clientToGame(clientData);
                }
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: {
                printf("(Client) %u disconnected.\n", event.peer->connectID);

                event.peer->data = NULL;
                this->connected = false;
                break;
            }
        }
    }
}

void Multiplayer::clientToGame(ClientData * clientData){
    Tetromino * tetromino;
    if(connectID == clientData->m2) {
        this->gameData->level = static_cast<int>(clientData->m6);
        this->gameData->score = clientData->m8;
        tetromino = Tetromino::create(static_cast<int>(clientData->m10));
        for(int i = 0; i < 200; i++) {
            this->gameData->board[i] = clientData->m4[i];
            this->gameData->boardOp[i] = clientData->m5[i];
        } 
        if(clientData->messageType == RESULTS_MESSAGE && clientData->m6 == 0) this->gameData->result = true;
    } else {
        this->gameData->level = static_cast<int>(clientData->m7);
        this->gameData->score = clientData->m9;
        tetromino = Tetromino::create(static_cast<int>(clientData->m11));
        for(int i = 0; i < 200; i++) {
            this->gameData->board[i] = clientData->m5[i];
            this->gameData->boardOp[i] = clientData->m4[i];
        }
        if(clientData->messageType == RESULTS_MESSAGE && clientData->m7 == 0) this->gameData->result = true;
    }
    for(int i = 0; i < 16; i++) this->gameData->tiles[i] = tetromino->getTiles()[i];
}

void Multiplayer::gameEndMenu() {
    std::unique_ptr<GameEnd> gameEnd = std::make_unique<GameEnd>(this->window, this->renderer);
    gameEnd->Setup(this->window, this->renderer);
    if(this->gameData->result) {
        gameEnd->changeText("You win!");
        printf("Ganhei!\n");
    }
    int choice = gameEnd->showgameend();
    switch (choice) {
        case 1:
            this->close = true;
            this->running = true;
            break;
    }
}

int Multiplayer::Run(char * ip) {  
   
    MultiGameView * gameView = new MultiGameView(this->window, this->renderer);

    if(Multiplayer::connect(ip) == EXIT_FAILURE) return 0;

    while(!(this->close)) {  
        Multiplayer::pollSDLEvent(peer);
        Multiplayer::handleServer();
        if(connected) {
            gameView->Draw(*(this->gameData));
            if(!running) gameView->DrawWaitStart();
            //if(results) gameView->DrawResults(*(this->gameData));
            if(results) Multiplayer::gameEndMenu();
        } else {
            gameView->DrawWaitConnection();
        }
        SDL_RenderPresent(this->renderer);
    }
    
    enet_peer_disconnect_now(peer, 0);

    return 0;
}
