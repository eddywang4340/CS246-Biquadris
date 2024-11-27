#include "player.h"

Player::Player(int level, std::string file): 
    studio{}, totalRowsCleared{0}, score{0}, highScore{0},
    lost{false}, isBlind{false}, isHeavy{false}, isForce{false}
{
    if(level == 0) lvl = new LevelZero(file);  // Fixed: Added LevelZero
    else if(level == 1) lvl = new LevelOne();
    else if(level == 2) lvl = new LevelTwo();
    else if(level == 3) lvl = new LevelThree(file);
    else lvl = new LevelFour(file);

    nextShape = lvl->getRand();
    shape = nullptr;
}

Player::~Player() {
    delete lvl;
    delete shape;
    delete nextShape;
}

void Player::updateHighScore() {
    if(score > highScore) {
        highScore = score;
    }
}

void Player::setNextLevel() {
    int currentLevel = lvl->getLevel();
    Level* newLevel = nullptr;
    
    if(currentLevel < 4) {
        switch(currentLevel + 1) {
            case 1: newLevel = new LevelOne(); break;
            case 2: newLevel = new LevelTwo(); break;
            case 3: newLevel = new LevelThree(""); break;
            case 4: newLevel = new LevelFour(""); break;
        }
        
        if(newLevel) {
            delete lvl;
            lvl = newLevel;
        }
    }
}

void Player::resetBoard() {
    studio = Studio();
    score = 0;
    totalRowsCleared = 0;
    lost = false;
    isBlind = false;
    isHeavy = false;
    isForce = false;
    
    delete shape;
    delete nextShape;
    shape = nullptr;
    nextShape = lvl->getRand();
}

void Player::renderRow(int n) {
    if(isBlind && n >= 2 && n <= 11) {
        for(int i = 0; i < 11; ++i) {
            if(i >= 2 && i <= 8) {
                std::cout << "?";
            } 
            else {
                std::cout << studio.charAt(i, n);
            }
        }
        return;
    }

    for(int i = 0; i < 11; ++i) {
        if(shape && n >= shape->getOT() && n < shape->getOT() + shape->getHeight() && i >= shape->getOL() && i < shape->getOL() + shape->getWidth()) {
            char shapeChar = shape->charAt(i - shape->getOL(), n - shape->getOT());
            if(shapeChar != ' ') {
                std::cout << shapeChar;
                continue;
            }
        }
        std::cout << studio.charAt(i, n);
    }
}

void Player::renderRowShape(int n) const {
    if(nextShape) {
        std::vector<std::vector<char>> grid = nextShape->getGrid();
        for(int i = 0; i < 4; ++i) {
            std::cout << grid[n][i];
        }
    } 
    else {
        std::cout << "    ";
    }
}