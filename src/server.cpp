#include "server.hpp"
#include <iostream>
#include <enet/enet.h>
#include <stdint.h>
#include "board.hpp"
#include "tetromino.hpp"
#include <chrono>

// PROXIMOS PASSOS:
// Terminar de implementar as funções handleCommand e lock and load;
// Implementar a visualização da proxima peça
// Implementar a pontuação no servidor
// Implementar o fim do jogo (tela)
// Implementar o começo do jogo (tela e espera)

Server::Server() { 

    Board * board1 = new Board();
    this->boards.push_back(board1);
   
    Board * board2 = new Board();
    this->boards.push_back(board2);

    Tetromino * tetromino1 = Tetromino::create(rand() % 7 + 2);
    this->tetrominos.push_back(tetromino1);

    Tetromino * tetromino2 = Tetromino::create(rand() % 7 + 2);
    this->tetrominos.push_back(tetromino2);

    this->nextIndex[0] = rand() % 7 + 2;
    this->nextIndex[1] = rand() % 7 + 2;
    
    Tetromino * tetromino3 = Tetromino::create(static_cast<int>(this->nextIndex[0]));
    this->nextTetrominos.push_back(tetromino3);

    Tetromino * tetromino4 = Tetromino::create(static_cast<int>(this->nextIndex[1]));
    this->nextTetrominos.push_back(tetromino4);

    this->players = 0;

    this->hasSwaped = false;

    this->counter = std::chrono::steady_clock::now();

    this->bothConnected = false;

    this->gameEnd = false;
}

Server::~Server() {
    enet_deinitialize();
    delete boards[0];
    delete boards[1];
    delete tetrominos[0];
    delete tetrominos[1];
    delete nextTetrominos[0];
    delete nextTetrominos[1];
    delete server;
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

void Server::lockAndLoad(int index) {
    this->boards[index]->lockTetromino(this->tetrominos[index]); 
    this->tetrominos[index] = this->nextTetrominos[index];
    this->nextIndex[index] = rand() % 7 + 2;
    this->nextTetrominos[index] = Tetromino::create(static_cast<int>(this->nextIndex[index]));
    this->hasSwaped = false;
}

void Server::getData(ClientData * clientData, uint32_t connectID) {
    clientData->messageType = STATE_MESSAGE;
    printf("A\n");
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
    clientData->m6 = this->boards[id]->getLevel();
    clientData->m7 = this->boards[id+1]->getLevel();
    clientData->m8 = this->boards[id]->getScore();
    clientData->m9 = this->boards[id+1]->getScore();
    clientData->m10 = this->nextIndex[id];
    clientData->m11 = this->nextIndex[id+1];
}

int Server::idToIndex(uint32_t connectID) {
    for(int i = 0; i < 2; i++) if(clients[i] == connectID) return i;
}

void Server::handleCommands(int command, uint32_t connectID) { 
    int position;
    int id = idToIndex(connectID);
    switch(command) { 
        case SPACE_BAR:
            while(this->boards[id]->isPositionValid(this->tetrominos[id]) == 0) {
                tetrominos[id]->moveDir(0);        
            }
            tetrominos[id]->moveDir(3);
            Server::lockAndLoad(id);
            break;
        case ARROW_LEFT:
        case ARROW_RIGHT:
            tetrominos[id]->moveDir(command);
            position = boards[id]->isPositionValid(tetrominos[id]);
            if(position != 0) tetrominos[id]->moveDir(-command);
            if(position == 2) Server::lockAndLoad(id);
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
        case SWAP:
            if(!hasSwaped){
                Tetromino * temp = this->tetrominos[id];
                this->nextTetrominos[id]->
                moveTo(this->tetrominos[id]->getX(), this->tetrominos[id]->getY());
                this->tetrominos[id] = this->nextTetrominos[id];
                this->nextTetrominos[id] = temp;

                this->hasSwaped = true;

                uint8_t inttemp = this->nextIndex[0];
                this->nextIndex[0] = this->nextIndex[1];
                this->nextIndex[1] = inttemp;
            }
    }
}

void Server::tryDescend() {
    const auto now{std::chrono::steady_clock::now()};
    const auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds> (now - this->counter);
    if(elapsed_milliseconds >= std::chrono::milliseconds(1000)) {
        counter = std::chrono::steady_clock::now();
        for(int id = 0; id < 2; id++) {
            tetrominos[id]->moveDir(0);
            int position = boards[id]->isPositionValid(tetrominos[id]);
            if(position != 0) {
                tetrominos[id]->moveDir(3);
                Server::lockAndLoad(id);
            }
        }
        ClientData * clientData = (ClientData *) malloc(sizeof(ClientData));
        Server::getData(clientData, 0);  
        ENetPacket *packet = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(this->server, 0, packet);
    } 

}

int Server::Run() {
    if(!Server::initServer()) {
        return 0;
    };

    int eventStatus;
    ENetEvent event;
    ClientData * clientData;
    ENetPacket *packet;
    while(1) {
        eventStatus = enet_host_service(server, &event, 0);

        if(eventStatus > 0) {
            switch(event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    std::cout << "(Server) We got a new connection from " << event.peer->address.host << 
                    " with id " << event.peer->connectID << "\n";
                    this->clients[players] = event.peer->connectID;
                    players++;
                    if(players == 2) bothConnected = true;
                    clientData = (ClientData *) malloc(sizeof(ClientData));

                    clientData->messageType = 13;
                    clientData->m2 = event.peer->connectID;
                    packet = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer, 0, packet);

                    Server::getData(clientData, 0);  
                    packet = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(server, 0, packet);
                    break; }
                case ENET_EVENT_TYPE_RECEIVE: {
                    if(bothConnected && !gameEnd) {
                        clientData = reinterpret_cast<ClientData*>(event.packet->data);
                        std::cout << "(Server) Message from client " << event.peer->connectID << " : " 
                            << static_cast<int>(clientData->m1) << "\n";
                        Server::handleCommands(static_cast<int>(clientData->m1), event.peer->connectID);

                        Server::getData(clientData, event.peer->connectID);  
                        packet = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
                        enet_host_broadcast(server, 0, packet);
                    }
                    break; }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    std::cout << "(Server) " << event.peer->connectID << " disconnected\n";
                    event.peer->data = NULL;
                    players--;
                    bothConnected = false;
                    if(players == 0) gameEnd = true;
                    break; }
            }
        }
        if(this->boards[0]->checkIfEnded()) {
            printf("1 acabou\n");
            gameEnd = true;
        }
        if(this->boards[1]->checkIfEnded()) {
            printf("2 acabou\n");
            gameEnd = true;
        }
        if(bothConnected && !gameEnd)Server::tryDescend();
    }
    return 1;
}
