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
};

class Server {
    private:
        ENetHost * server = nullptr;
        std::vector<Board*> boards;
        std::vector<Tetromino*> tetrominos;
        uint32_t clients[2];

        void getData(ClientData * clientData, uint32_t connectID);
        void handleCommands(int command, uint32_t connectID);
        bool initServer();
        int idToIndex(uint32_t connectID);
        int players;


    public: 
        Server();
        ~Server();
        int Run();
};

#endif
