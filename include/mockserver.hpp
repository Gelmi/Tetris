#ifndef MOCKSERVER_HPP
#define MOCKSERVER_HPP

#include "board.hpp"
#include "tetromino.hpp"
#include "gamedata.hpp"

class MockServer {
    private:
        Board * board;
        Tetromino * tetromino;
        int counter;

    public:
        MockServer();
        void update(int command);
        GameData getState();
        
};

#endif
