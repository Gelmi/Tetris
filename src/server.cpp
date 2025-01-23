#include "server.hpp"
#include <iostream>
#include <enet/enet.h>
#include <stdint.h>
#include "board.hpp"
#include "tetromino.hpp"

// PROXIMOS PASSOS:
// COMEÇAR A CONSTRUIR O SERVIDOR:
// MAKE FILE COM OS INCLUDES DIVERSOS PARA O SERVER
// INSTANCIAR DOIS BOARDS
// COMO CONSTRUIR CLIENT DATA APARTIR DA CLASSE BOARD
// DEPOIS RENDERIZAR ESSAS DUAS DATAS SOBRE O CLIENT
// TESTAR COM O MOVIMENTO DE UM QUADRADO
// POSSIVELMENTE CRIAR UMA CLASSE NETWORKMANAGER

Server::Server() {
    //Initialize Enet
    if(enet_initialize() != 0) {
        std::cerr << "An error occured while initializing Enet.\n";
    }

    Board * board1 = new Board();
    this->boards.push_back(board1);
   
    Board * board2 = new Board();
    this->boards.push_back(board2);

    Tetromino * tetromino1 = Tetromino::create(rand() % 7 + 2);
    this->tetrominos.push_back(tetromino1);

    Tetromino * tetromino2 = Tetromino::create(rand() % 7 + 2);
    this->tetrominos.push_back(tetromino2);

    players = 0;

}

Server::~Server() {
    enet_deinitialize();
}

bool Server::initServer() {

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;
    
    this->server = enet_host_create(&address, 32, 2, 0, 0);

    if(this->server == nullptr) {
        std::cerr << "An error occured while trying to create an ENet server host\n";
        return false;
    }

    return true;
}

void Server::getData(ClientData * clientData, uint32_t connectID) {
    clientData->messageType = STATE_MESSAGE;
    int id = 0;
    clientData->m2 = clients[id];
    clientData->m3 = clients[id+1];
    for(int i = 0; i < 200; i++) {
        clientData->m4[i] = this->boards[id]->getTiles()[i];
        clientData->m5[i] = this->boards[id+1]->getTiles()[i];
    }
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++) {
            if(this->tetrominos[id]->getTiles()[this->tetrominos[id]->atPos(i,j)] != 0) {
                clientData->m4[this->boards[id]->atPos(this->tetrominos[id]->getX()+j, this->tetrominos[id]->getY()+i)]
                    = this->tetrominos[id]->getTiles()[this->tetrominos[id]->atPos(i,j)];
            }
            if(this->tetrominos[id+1]->getTiles()[this->tetrominos[id+1]->atPos(i,j)] != 0) {
                clientData->m5[this->boards[id+1]->atPos(this->tetrominos[id+1]->getX()+j, this->tetrominos[id+1]->getY()+i)]
                    = this->tetrominos[id+1]->getTiles()[this->tetrominos[id+1]->atPos(i,j)];
            }
        }
    }
}

int Server::idToIndex(uint32_t connectID) {
    for(int i = 0; i < 2; i++) if(clients[i] == connectID) return i;
}

void Server::handleCommands(int command, uint32_t connectID) { 
    int position;
    int id = idToIndex(connectID);
    switch(command) { 
        case ARROW_LEFT:
        case ARROW_RIGHT:
            tetrominos[id]->moveDir(command);
            position = boards[id]->isPositionValid(tetrominos[id]);
            if(position != 0) tetrominos[id]->moveDir(-command);
            break;
        case ARROW_UP: 
            tetrominos[id]->rotateLeft();
            position = boards[id]->isPositionValid(tetrominos[id]);
            if(position != 0) tetrominos[id]->rotateRight();
            break;
        case ARROW_DOWN:
            tetrominos[id]->rotateRight();         
            position = boards[id]->isPositionValid(tetrominos[id]);
            if(position != 0) tetrominos[id]->rotateLeft();
            break;
    } 
}

int Server::Run() {
    if(!Server::initServer()) {
        return 0;
    };

    int eventStatus;
    ENetEvent event;
    while(1) {
        eventStatus = enet_host_service(server, &event, 0);

        if(eventStatus > 0) {
            switch(event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    std::cout << "(Server) We got a new connection from " << event.peer->address.host << 
                    " with id " << event.peer->connectID << "\n";
                    //this->clients.push_back(event.peer->connectID);
                    this->clients[players] = event.peer->connectID;
                    players++;
                    ClientData clientData;
                    clientData.messageType = 13;
                    clientData.m2 = event.peer->connectID;
                    ENetPacket *packet = enet_packet_create(&clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer, 0, packet);
                    break; }
                case ENET_EVENT_TYPE_RECEIVE: {
                    ClientData * clientData = reinterpret_cast<ClientData*>(event.packet->data);
                    std::cout << "(Server) Message from client " << event.peer->connectID << " : " 
                        << static_cast<int>(clientData->m1) << "\n";
                    Server::handleCommands(static_cast<int>(clientData->m1), event.peer->connectID);

                    Server::getData(clientData, event.peer->connectID);  
                    ENetPacket *packet = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(server, 0, packet);

                    break; }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    std::cout << "(Server) " << event.peer->connectID << " disconnected\n";
                    event.peer->data = NULL;
                    break; }
            }
        }
    }
    return 1;
}
