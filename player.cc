#include "player.h"
#include "shape.h"

using namespace std;

Player::Player(int level, std::string file): 
    studio{}, totalRowsCleared{0}, highScore{0},
    lost{false}, isBlind{false}, isHeavy{false}, isForce{false}, isRand{file.length() == 0}
{
    // Initialize level based on parameter
    if(level == 0) { lvl = new LevelOne(); } /// no level 0
    else if(level == 1) { lvl = new LevelOne(); }
    else if(level == 2) { lvl = new LevelTwo(); }
    else if(level == 3) { lvl = new LevelThree(file); }
    else { lvl = new LevelFour(file); }
	
	shape = lvl->getRand();
	nextShape = lvl->getRand();
}

Player::~Player() {
    delete lvl;
    delete shape;
    delete nextShape;
}

void Player::setNextLevel() { //tested
    int currentLevel = lvl->getLevel();
	cout << "Current Level: " << currentLevel << endl;
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

void Player::setDownLevel() { //tested
    int currentLevel = lvl->getLevel();
    Level* newLevel = nullptr;
    
    if(currentLevel > 0) {
        switch(currentLevel - 1) {
			case 0: newLevel = new LevelOne(); break;
            case 1: newLevel = new LevelOne(); break;
            case 2: newLevel = new LevelTwo(); break;
            case 3: newLevel = new LevelThree(""); break;
        }
        
        if(newLevel) {
            delete lvl;
            lvl = newLevel;
        }
    }
}

void Player::resetBoard() {
    studio = Studio();
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

bool Player::handleMovement(int moveCol, int moveRow) {
    if(moveCol != 0 && canMove(0, moveCol)) { // horizontal
        shape->move(moveCol, 0);
        
        int down = moveRow;
        if(isHeavy) down += 2;
        else if(lvl->getLevel() >= 3) down += 1;
        
        if(down > 0) {
            if(!canMove(down, 0)) {
                return true;
            }
            shape->move(0, down);
        }
    }
    
    if(moveRow > 0 && canMove(moveRow, 0)) {
        shape->move(0, moveRow);
    }
    
    return false;
}
/* 
void Player::setNextShape() {
	if (nextShape) shape = nextShape;
    if(isRand) nextShape = lvl->getRand();
    else nextShape = nullptr; // lvl->getNotRand();
} */

void Player::updateTurn(string cmd) {
    if(shape == nullptr) shape = nextShape;
    
    //Level commands
    if(cmd == "levelup") {
        setNextLevel();
        return;
    } 
    else if(cmd == "leveldown") {
        setDownLevel();
        return;
    }

	if (cmd == "clockwise") {
		shape->rotateCW();
	} 
    else if (cmd == "counterclockwise") {
		shape->rotateCCW();
	}


    //Movement commands
    int moveRow = 0, moveCol = 0;
    
    if(cmd == "left") moveCol = -1;
    else if(cmd == "right") moveCol = 1;
    else if(cmd == "down") moveRow = 1;
    else if(cmd == "drop") dropBlock();

    if(handleMovement(moveCol, moveRow)) dropBlock();
}

void Player::dropBlock() { // tested
    while(canMove(1, 0)) {
        shape->move(0, 1);
    }

    vector<vector<char>> board = studio.getBoard();
    int top = shape->getT();
    int left = shape->getL();

    for(int i = 0; i < shape->getHeight(); ++i) {
        for(int j = 0; j < shape->getWidth(); ++j) {
            char shapeChar = shape->charAt(j, i);
            if(shapeChar != ' ') {
                board[top + i][left + j] = shapeChar;
            }
        }
    }
    
    if(top < 3) setLost();
    
    studio.setBoard(board);
    
    delete shape;
    shape = nextShape;
	nextShape = lvl->getRand();
    
    while(studio.canRemove() != -1) {
        studio.removeRow();
        totalRowsCleared++;
    }
}

int Player::getHighScore() {
    highScore = max(highScore, getScore());
    return highScore; 
}

bool Player::canMove(int r, int c) {
    int nt = shape->getT() + r;
    int nl = shape->getL() + c;
    
    if(nl < 0 || nl + shape->getWidth() > 11 ||
        nt < 0 || nt + shape->getHeight() > 18) {
        return false;
    }

    for(int i = 0; i < shape->getHeight(); ++i) {
        for(int j = 0; j < shape->getWidth(); ++j) {
            if(shape->charAt(j, i) != ' ' && studio.charAt(nl + j, nt + i) != ' ') {
                return false;
            }
        }
    }
    
    return true;
}

void Player::renderRow(int n) { // tested
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
        if(shape && n >= shape->getT() && n < shape->getT() + shape->getHeight() && i >= shape->getL() && i < shape->getL() + shape->getWidth()) {
            char shapeChar = shape->charAt(i - shape->getL(), n - shape->getT());
            if(shapeChar != ' ') {
                std::cout << shapeChar;
                continue;
            }
        }
        std::cout << studio.charAt(i, n);
    }
}

void Player::renderRowShape(int n) const { // tested
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