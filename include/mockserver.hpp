#ifndef MOCKSERVER_HPP
#define MOCKSERVER_HPP

#include "board.hpp"
#include "tetromino.hpp"
#include "gamedata.hpp"
#include <memory>

class MockServer {
    private:
        std::shared_ptr<Board> board;
        std::shared_ptr<Tetromino> tetromino, nextTetromino;
        bool hasSwaped;
        int counter;

    public:
        MockServer();
        void update(int command, GameData data);
        GameData getState();
        void lockAndLoad();
        
};

#endif
