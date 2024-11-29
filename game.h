#ifndef GAME_H
#define GAME_H

// import classes
#include "player.h"
#include "xwindow.h"
#include "shape.h"
#include "gameProperties.h"

class Game {
    // private members
    Player player1, player2;
    std::vector<std::vector<char>> player1_board;
    std::vector<std::vector<char>> player2_board;
    int turnAcc;
    Xwindow *window;
    bool isGraphics;

    GameProperties gameProps;

    // public members
    public:
        Game(int player1_lvl, int player2_lvl, std::string player1_file = "", std::string player2_file = "", bool isGraphics = false);
        ~Game();
        std::string getWinner();
        void update();
        void render();
        void restart();
        void initializeGraphics();
};

#endif
