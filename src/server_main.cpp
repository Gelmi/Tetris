#include "server.hpp"
#include <enet/enet.h>
#include <iostream>

int main() {
    if(enet_initialize() != 0) {
        std::cerr << "An error occured while initializing Enet.\n";
    }
    Server * server = new Server();
    return server->Run();
}
