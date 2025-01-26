/**
 * @file server.cpp
 * @author Gabriel and Guilherme 
 * @brief This file handles the all the servidor's management
 * @version 0.1
 * @date 2025-01-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "server.hpp"
#include <iostream>
#include <enet/enet.h>
#include <stdint.h>
#include "board.hpp"
#include "tetromino.hpp"
#include <chrono>
#include <memory>
#include "constants.hpp"

/**
 * @brief Constructs a Server object and initializes game boards and Tetrominos.
 *
 * This constructor:
 * - Creates two Board objects and stores them in the boards vector.
 * - Creates two initial Tetrominos (one for each board/player).
 * - Creates two "next" Tetrominos (the upcoming pieces for each player).
 * - Initializes important server state variables (e.g., player count, 
 *   swap flags, connection status).
 */
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
    this->playerIndex = 0;

    this->hasSwaped[0] = false;
    this->hasSwaped[1] = false;

    this->counter = std::chrono::steady_clock::now();

    this->bothConnected = false;

    this->gameEnd = false;
}

/**
 * @brief Destroys the Server object and cleans up resources.
 * 
 * This destructor:
 * - Deinitializes ENet.
 * - Deletes dynamically allocated Board objects.
 * - Deletes dynamically allocated Tetromino objects.
 * - Deletes the ENet server host if it exists.
 */
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

/**
 * @brief Initializes the ENet server.
 *
 * @return True if the server was successfully created, otherwise false.
 */
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

/**
 * @brief Locks the current Tetromino of a player into the board and spawns the next one.
 *
 * This method:
 * - Locks the Tetromino for the specified player index.
 * - Adds garbage rows to the opponent’s board, depending on the lines cleared.
 * - Swaps the current Tetromino with the next Tetromino.
 * - Randomly generates a new "next" Tetromino.
 * - Checks if the newly spawned Tetromino is in a valid position. If not, sets the game to end.
 * - Sends end-of-game messages if necessary.
 *
 * @param index The index of the current player (0 or 1).
 */
void Server::lockAndLoad(int index) {
    boards[(index+1)%2]->addRows(this->boards[index]->lockTetromino(this->tetrominos[index]));
    this->tetrominos[index] = this->nextTetrominos[index];
    this->nextIndex[index] = rand() % 7 + 2;
    this->nextTetrominos[index] = Tetromino::create(static_cast<int>(this->nextIndex[index]));
    this->hasSwaped[index] = false;
    if(this->boards[index]->isPositionValid(this->tetrominos[index]) == 2) gameEnd = true;
    Server::sendEndMessage(index);
}

/**
 * @brief Populates the given ClientData structure with the current game state.
 *
 * This method:
 * - Sets the message type to STATE_MESSAGE.
 * - Copies the client IDs into the structure.
 * - Copies board tile data for both players.
 * - Overlays the current Tetrominos onto the board data.
 * - Copies each board's level and score.
 * - Copies the index (type) of the upcoming Tetrominos.
 *
 * @param clientData A pointer to a ClientData structure to fill with the current state.
 */
void Server::getData(ClientData * clientData) {
    clientData->messageType = STATE_MESSAGE;
    int id = 0;
    clientData->m2 = clients[id];
    clientData->m3 = clients[id+1];

    // Copy board tiles
    for(int i = 0; i < 200; i++) {
        clientData->m4[i] = this->boards[id]->getTiles()[i];
        clientData->m5[i] = this->boards[id+1]->getTiles()[i];
    }

    // Overlay current Tetrominos onto board data
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++) {
            // First player's Tetromino
            if(this->tetrominos[id]->getTiles()[this->tetrominos[id]->atPos(i,j)] != 0) {
                clientData->m4[this->boards[id]->atPos(this->tetrominos[id]->getX()+j, this->tetrominos[id]->getY()+i)]
                    = this->tetrominos[id]->getTiles()[this->tetrominos[id]->atPos(i,j)];
            }
            // Second player's Tetromino
            if(this->tetrominos[id+1]->getTiles()[this->tetrominos[id+1]->atPos(i,j)] != 0) {
                clientData->m5[this->boards[id+1]->atPos(this->tetrominos[id+1]->getX()+j, this->tetrominos[id+1]->getY()+i)]
                    = this->tetrominos[id+1]->getTiles()[this->tetrominos[id+1]->atPos(i,j)];
            }
        }
    }

    // Board levels, scores, and upcoming piece indexes
    clientData->m6 = this->boards[id]->getLevel();
    clientData->m7 = this->boards[id+1]->getLevel();
    clientData->m8 = this->boards[id]->getScore();
    clientData->m9 = this->boards[id+1]->getScore();
    clientData->m10 = this->nextIndex[id];
    clientData->m11 = this->nextIndex[id+1];
}

/**
 * @brief Finds the player index (0 or 1) for a given connection ID.
 *
 * @param connectID The ENet connection ID.
 * @return The index of the player (0 or 1), or -1 if not found.
 */
int Server::idToIndex(uint32_t connectID) {
    for(int i = 0; i < 2; i++) if(clients[i] == connectID) return i;
    return -1;
}

/**
 * @brief Handles commands received from a client.
 *
 * Supported commands include:
 * - SPACE_BAR (drop piece)
 * - ARROW_LEFT / ARROW_RIGHT (move piece horizontally)
 * - ARROW_UP / ARROW_DOWN (rotate piece)
 * - SWAP (swap held piece with next piece)
 *
 * @param command The command code received from the client.
 * @param connectID The connection ID of the client sending the command.
 */
void Server::handleCommands(int command, uint32_t connectID) { 
    int position;
    int id = idToIndex(connectID);
    switch(command) { 
        case SPACE_BAR:  // Hard drop
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
            if(!hasSwaped[id]){
                Tetromino * temp = this->tetrominos[id];
                this->nextTetrominos[id]->
                moveTo(this->tetrominos[id]->getX(), this->tetrominos[id]->getY());
                this->tetrominos[id] = this->nextTetrominos[id];
                this->nextTetrominos[id] = temp;
                this->nextTetrominos[id]->moveTo(0,0);

                this->hasSwaped[id] = true;

                uint8_t inttemp = this->nextIndex[0];
                this->nextIndex[0] = this->nextIndex[1];
                this->nextIndex[1] = inttemp;
            }
    }
}

/**
 * @brief Attempts to move each player's Tetromino down at fixed intervals.
 *
 * If the move down is invalid, the Tetromino is moved back up one line 
 * and locked into place (triggering a new piece). The game state is 
 * then broadcast to all connected clients.
 */
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
        sendStateToClients();
    } 
}

/**
 * @brief Sends an end-of-round or end-of-game message to all clients, if needed.
 *
 * This function sets up a ClientData structure indicating which player has ended 
 * the game or caused the round to end, and then broadcasts it to all connected clients.
 *
 * @param index The index of the player who just locked a piece.
 * @return True if the game has ended, otherwise false.
 */
bool Server::sendEndMessage(int index) {
    std::unique_ptr<ClientData> clientData = std::make_unique<ClientData>();
    clientData->messageType = RESULTS_MESSAGE;
    clientData->m2 = clients[0];
    clientData->m3 = clients[1];
    clientData->m6 = 0;
    clientData->m7 = 0;
    if(index == 0) clientData->m6 = 1; 
    else clientData->m7 = 1;
    if(gameEnd) {
        ENetPacket * packet = enet_packet_create(clientData.get(), sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(server, 0, packet);
        printf("Enviei\n");
    }
    printf("Result: %d, %d\n", clientData->m6, clientData->m7);
    return gameEnd;
}

/**
 * @brief Checks if either player's board is in a losing state and notifies clients.
 *
 * If any board has reached a losing condition, this method broadcasts a 
 * RESULTS_MESSAGE to all clients to indicate which player lost.
 *
 * @return True if the game has ended, otherwise false.
 */
bool Server::checkIfEnded() {
    std::unique_ptr<ClientData> clientData = std::make_unique<ClientData>();
    clientData->messageType = RESULTS_MESSAGE;
    clientData->m2 = clients[0];
    clientData->m3 = clients[1];
    clientData->m6 = 0;
    clientData->m7 = 0;
    if(this->boards[0]->checkIfEnded()) {
        gameEnd = true;
        clientData->m6 = 1; 
    }
    if(this->boards[1]->checkIfEnded()) {
        gameEnd = true;
        clientData->m7 = 1; 
    }
    if(gameEnd) {
        ENetPacket * packet = enet_packet_create(clientData.get(), sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
        enet_host_broadcast(server, 0, packet);
        printf("Enviei\n");
    }
    printf("Result: %d, %d\n", clientData->m6, clientData->m7);
    return gameEnd;
}

/**
 * @brief Restarts the game by resetting boards, Tetrominos, and server state.
 *
 * This function re-initializes:
 * - The two boards.
 * - The current and next Tetrominos.
 * - Swap flags, timers, and connection state.
 * - The gameEnd flag.
 */
void Server::restartGame() {
    this->boards[0] = new Board();
    this->boards[1] = new Board();
       
    this->tetrominos[0] = Tetromino::create(rand() % 7 + 2);
    this->tetrominos[1] = Tetromino::create(rand() % 7 + 2);

    this->nextIndex[0] = rand() % 7 + 2;
    this->nextIndex[1] = rand() % 7 + 2;
    
    this->nextTetrominos[0] = Tetromino::create(static_cast<int>(this->nextIndex[0]));
    this->nextTetrominos[1] = Tetromino::create(static_cast<int>(this->nextIndex[1]));

    this->hasSwaped[0] = false;
    this->hasSwaped[1] = false;

    this->counter = std::chrono::steady_clock::now();

    this->bothConnected = false;

    this->gameEnd = false;
};

/**
 * @brief Sends the current state of the game to all connected clients.
 *
 * This function constructs a ClientData message by calling getData(), then 
 * broadcasts it to all connected clients. It also flushes the ENet host 
 * to ensure timely delivery.
 */
void Server::sendStateToClients() {
    std::unique_ptr<ClientData> clientData = std::make_unique<ClientData>();
    Server::getData(clientData.get());  
    ENetPacket * packet = enet_packet_create(clientData.get(), sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(server, 0, packet);
    enet_host_flush(server);
}

/**
 * @brief Sends a connection message to a newly connected client.
 *
 * The message includes the connecting client's ID (connectID) 
 * and is sent reliably on channel 0.
 *
 * @param peer A pointer to the ENetPeer representing the connected client.
 */
void Server::sendConnectMessage(ENetPeer * peer) {
    ClientData * clientData = (ClientData *) malloc(sizeof(ClientData));
    clientData->messageType = 13;
    clientData->m2 = peer->connectID;
    ENetPacket * packet = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(server);
}

/**
 * @brief Sends a start message to all connected clients, indicating the game is beginning.
 */
void Server::sendStartMessage() {
    std::unique_ptr<ClientData> clientData = std::make_unique<ClientData>();
    clientData->messageType = START_MESSAGE;
    ENetPacket * packet = enet_packet_create(clientData.get(), sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(server, 0, packet);
    enet_host_flush(server);
}

/**
 * @brief Runs the main event loop of the server.
 *
 * This function continuously processes ENet events (connect, receive, disconnect). 
 * Once both players have connected, it handles commands from the clients and attempts 
 * to move pieces down at regular intervals. 
 *
 * @return An integer exit code; returns 0 if server initialization fails, otherwise runs indefinitely.
 */
int Server::Run() {
    if(!Server::initServer()) {
        return 0;
    };

    int eventStatus;
    ENetEvent event;
    int limite = 1;
    while(1) {
        eventStatus = enet_host_service(server, &event, 0);

        if(eventStatus > 0) {
            switch(event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    std::cout << "(Server) We got a new connection from " << event.peer->address.host << 
                    " with id " << event.peer->connectID << "\n";
                    this->clients[players] = event.peer->connectID;
                    players++;

                    if(!gameEnd && players == 2) {
                        bothConnected = true;
                        gameEnd= false;
                        const auto old{std::chrono::steady_clock::now()};
                        while ((std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now()-old)) < std::chrono::milliseconds(3000));
                        sendStartMessage();
                        
                    } 

                    sendConnectMessage(event.peer);
                    //sendStateToClients();

                    enet_packet_destroy(event.packet);
                    break; }
                case ENET_EVENT_TYPE_RECEIVE: {
                    if(bothConnected && !gameEnd) {
                        ClientData * clientData = reinterpret_cast<ClientData*>(event.packet->data);
                        std::cout << "(Server) Message from client " << event.peer->connectID << " : " 
                            << static_cast<int>(clientData->m1) << "\n";
                        Server::handleCommands(static_cast<int>(clientData->m1), event.peer->connectID);
                        sendStateToClients();    
                        enet_packet_destroy(event.packet);
                    }
                    break; }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    std::cout << "(Server) " << event.peer->connectID << " disconnected\n";
                    event.peer->data = NULL;
                    players--;
                    bothConnected = false;
                    gameEnd = true;
                    if(players == 0) {
                        Server::restartGame();
                        gameEnd = false;
                    };
                    break; }
            }
        }
        if(bothConnected && !gameEnd)Server::tryDescend();
    }
    return 1;
}
