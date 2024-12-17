#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include<SDL.h>

class GameData {
    public:
        int board[200];
        int tetromino[16];
        int x, y, r;
        SDL_Color color;
        GameData() : x(0), y(0), r(0){
            color = {255, 255, 255, 255};
            for(int i = 0; i < 200; i++) {
                board[i] = 0;
                if(i<16) tetromino[i] = 0;
            }
        };
};

#endif 
