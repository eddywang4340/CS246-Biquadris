#ifndef GAME_H
#define GAME_H

// import classes
#include "player.h"
#include "shapeObserver.h"
#include "shape.h"

#include "xwindow.h"
#include "shape.h"
// #include "gameproperties.h"

class Game : public ShapeObserver {
    // private members
    Player player1, player2;
    // GameProperties &GP;
    int turnAcc;
    Xwindow *window;
    bool isGraphics;

    // public members
    public:
        Game(int player1_lvl, int player2_lvl, std::string player1_file = "", std::string player2_file = "", bool isGraphics = false);
        ~Game();
        std::string getWinner();
        void update();
        void render();
        void restart();
        void initializeGraphics();

        void onShapeMove(Shape* shape, int oldX, int oldY);
};

#endif
