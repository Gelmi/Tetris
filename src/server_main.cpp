#include "server.hpp"

int main() {
    Server * server = new Server();
    return server->Run();
}
