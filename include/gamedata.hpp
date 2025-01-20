#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include<SDL.h>

class GameData {
    public:
        int score, level, rows;
        int board[200], tiles[16];
        GameData() : score(0), level(0), rows(0) {
            for(int i = 0; i < 200; i++) board[i] = 0;
            for(int i = 0; i < 16; i++) tiles[i] = 0;
        };
};

#endif 
