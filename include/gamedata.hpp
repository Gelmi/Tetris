#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

class GameData {
    public:
        int board[200];
        int tetromino[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        int x, y, r, t;
        GameData() : x(0), y(0), r(0), t(0){
            for(int i = 0; i < 200; i++) {
                board[i] = 1;
                if(i<16) tetromino[i] = 1;
            }
        };
};

#endif 
