#ifndef GAME_H
#define GAME_H

// import classes
#include "player.h"
#include "gameproperties.h"

class Game {
    // private members
    Player &Player1;
    Player &Player2;
    GameProperties &GP;
    int turnAcc;

    // public members
    public:
        Game(Player &p1, Player &p2, GameProperties &g, int turn) : Player1{p1}, Player2{p2}, GP{g}, turnAcc{turn} {}
        std::string getWinner();
        void update();
        void render();
        void restart();
};

#endif
