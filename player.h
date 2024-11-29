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
    Shape* shadowShape;
	ifstream filestream;
    
    int totalRowsCleared;
    int highScore;
    bool lost, isBlind, isHeavy, isForce, isRand;

    void handleMovement(int moveCol, int moveRow);
    
    void generateShadow();
    int calculateDropDistance();

public:
    Player(int lvl = 0, string file = "");
    ~Player();

    void updateTurn(std::string cmd);
    std::string renderRow(int n);
    std::string renderRowShape(int n) const;
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
    void setShape(char c);
	void setNextShape(char c);
    
    void setNextLevel();
	void setDownLevel();
    void resetBoard();
};

#endif
