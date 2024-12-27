#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include<SDL.h>

class GameData {
    public:
        int board[200];
        GameData() {
            for(int i = 0; i < 200; i++) board[i] = 0;
        };
};

#endif 
