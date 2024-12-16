#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

class GameData {
    public:
        int board[200];
        int tetromino[16] = {0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0};
        int x, y, r, t;
        GameData() : x(0), y(0), r(0), t(0){
            for(int i = 0; i < 200; i++) {
                board[i] = 0;
            }
            board[199] = 1;
            board[198] = 2;
        };
};

#endif 
