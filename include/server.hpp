#ifndef SERVER_HPP
#define SERVER_HPP

#include <enet/enet.h>
#include "board.hpp"
#include <vector>
#include "constants.hpp"

struct ClientData {
    int8_t messageType;
    int8_t m1;
    uint32_t m2;
    uint32_t m3;
    uint8_t m4[200];
    uint8_t m5[200];
    uint8_t padding[2];
};

class Server {
    private:
        ENetHost * server = nullptr;
        std::vector<Board*> boards;
        std::vector<Tetromino*> tetrominos;
        std::vector<Tetromino*> nextTetrominos;
        uint32_t clients[2];
        int players;
        bool hasSwaped;
        int counter;

        void getData(ClientData * clientData, uint32_t connectID);
        void handleCommands(int command, uint32_t connectID);
        bool initServer();
        int idToIndex(uint32_t connectID);
        void lockAndLoad();

    public: 
        Server();
        ~Server();
        int Run();
};

#endif
