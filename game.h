#ifndef GAME_H
#define GAME_H

// import classes
#include "player.h"
// #include "gameproperties.h"

class Game {
    // private members
    Player player1, player2;
    // GameProperties &GP;
    int turnAcc;

    // public members
    public:
        Game(int player1_lvl, int player2_lvl, std::string player1_file = "", std::string player2_file = "");
        std::string getWinner();
        void update();
        void render();
        void restart();
};

#endif
