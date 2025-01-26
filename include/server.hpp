#ifndef SERVER_HPP
#define SERVER_HPP

#include <enet/enet.h>
#include "board.hpp"
#include <vector>
#include "constants.hpp"
#include <chrono>

struct ClientData {
    int8_t messageType;
    int8_t m1;
    uint32_t m2, m3;
    uint8_t m4[200], m5[200];
    uint8_t m6, m7;
    uint32_t m8, m9;
    uint8_t m10, m11;
    uint8_t padding[2];
};

class Server {
    private:
        ENetHost * server = nullptr;
        std::vector<Board*> boards;
        std::vector<Tetromino*> tetrominos;
        std::vector<Tetromino*> nextTetrominos;
        uint8_t nextIndex[4];
        uint32_t clients[2];
        int players;
        int playerIndex;
        bool hasSwaped[2];
        bool bothConnected;
        bool gameEnd;
        std::chrono::steady_clock::time_point counter;

        void getData(ClientData * clientData);
        void handleCommands(int command, uint32_t connectID);
        bool initServer();
        int idToIndex(uint32_t connectID);
        void lockAndLoad(int index);
        void tryDescend();
        bool checkIfEnded();
        void restartGame();
        ClientData * createClientData();
        void sendStateToClients();
        void sendConnectMessage(ENetPeer * peer);
        void sendStartMessage();

    public: 
        Server();
        ~Server();
        int Run();
};

#endif
