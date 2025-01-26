#ifndef MULTIPLAYER_HPP
#define MULTIPLAYER_HPP

#include <SDL.h>
#include "view.hpp"
#include <enet/enet.h>
#include "gamedata.hpp"

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

class Multiplayer : public View {
    public:
        Multiplayer(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer)
            : View(sharedWindow, sharedRenderer) {};
        ~Multiplayer();
        void Setup(SDL_Window * sharedWindow, SDL_Renderer * sharedRenderer);
        int Run();

    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
        bool close;
        ENetAddress address;
        ENetHost * client;
        ENetPeer * peer;
        ENetEvent event;
        GameData * gameData;
        int eventStatus;
        bool connected;
        bool running;
        uint32_t connectID;

        void pollSDLEvent(ENetPeer * peer);
        int connect();
        void handleServer();
        void clientToGame(ClientData * clientData);
};

#endif
