#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include "studio.h"
#include "shape.h"

#include <string>
#include <iostream>

class Player {
    Level* lvl;
    Studio studio;
    Shape* shape;
    Shape* nextShape;
    
    int totalRowsCleared;
    int highScore;
    bool lost, isBlind, isHeavy, isForce;

    bool handleMovement(int col, int row);

public:
    Player(int lvl = 0, std::string file = "test.in");
    ~Player();

    void updateTurn(std::string cmd);
    void renderRow(int n);
    void renderRowShape(int n) const;
    bool canMove(int r, int c);
    void dropBlock();

    int getRowsCleared() const { return totalRowsCleared; }
    void updateRowsCleared(int rows) { totalRowsCleared += rows; }
    int getScore() const { return (lvl->getLevel() + totalRowsCleared)*(lvl->getLevel() + totalRowsCleared); }
    int getLevel() const { return lvl->getLevel(); }
    int getHighScore();
    bool getLost() const { return lost; }
    void setLost() { lost = true; }

    void setBlind() { isBlind = true; }
    void setHeavy() { isHeavy = true; }
    void setForce() { isForce = true; }
    
    void setNextLevel();
	void setDownLevel();
    void resetBoard();
};

#endif
