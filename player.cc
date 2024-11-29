#include "player.h"
#include "shape.h"
#include <string>
#include <sstream>

using namespace std;

Player::Player(int level): 
    studio{}, totalRowsCleared{0}, highScore{0},
    lost{false}, isBlind{false}, isHeavy{false}, isForce{false}, isRand{true}, file{}, shape{nullptr}, nextShape{nullptr}, shadowShape(nullptr)
{
    // Initialize level based on parameter
    if(level == 0) { 
		lvl = new LevelZero(); 
		cout << "Please input a file URL: " << endl;
		string str;
		cin >> str;	
		file.open(str);
		isRand = false;
	}
    else if(level == 1) { lvl = new LevelOne(); }
    else if(level == 2) { lvl = new LevelTwo(); }
    else if(level == 3) { lvl = new LevelThree(); }
    else { lvl = new LevelFour(); }

	char c; 
	
	if (level == 0 && file.is_open()) {
		if (file.get(c)) setShape(c);
		else { shape = lvl->getRand(); }
		if (file.get(c)) setNextShape(c);
		else { nextShape = lvl->getRand(); }
	} else {
		shape = lvl->getRand();
		nextShape = lvl->getRand();
	}
    generateShadow();
}

Player::~Player() {
    delete lvl;
    delete shape;
    delete nextShape;
    delete shadowShape;
}

void Player::setNextLevel() { //tested
    int currentLevel = lvl->getLevel();
    Level* newLevel = nullptr;
    
    if(currentLevel < 4) {
        switch(currentLevel + 1) {
            case 1: newLevel = new LevelOne(); break;
            case 2: newLevel = new LevelTwo(); break;
            case 3: newLevel = new LevelThree(); break;
            case 4: newLevel = new LevelFour(); break;
        }
        
        if(newLevel) {
            delete lvl;
            lvl = newLevel;
        }
    }

	cout << "You are now " << lvl->getLevel() << endl;
}

void Player::setDownLevel() { //tested
    int currentLevel = lvl->getLevel();
    Level* newLevel = nullptr;
    
    if(currentLevel > 0) {
        switch(currentLevel - 1) {
			case 0: newLevel = new LevelZero(); break;
            case 1: newLevel = new LevelOne(); break;
            case 2: newLevel = new LevelTwo(); break;
            case 3: newLevel = new LevelThree(); break;
        }
        
        if(newLevel) {
            delete lvl;
            lvl = newLevel;
        }
    }
	cout << "You are now Level " << lvl->getLevel() << endl;
	cout << "-----------" << endl;
}

void Player::resetBoard() {
    studio = Studio();
    totalRowsCleared = 0;
    lost = false;
    isBlind = false;
    isHeavy = false;
    isForce = false;
	isRand = false;
    
    if (shape) delete shape;
    if (nextShape) delete nextShape;
    if (shadowShape) delete shadowShape;
    shadowShape = nullptr;

	char c;

    if (lvl->getLevel() == 0 && file.is_open()) {
		if (file.get(c)) setShape(c);
		else { shape = lvl->getRand(); }
		if (file.get(c)) setNextShape(c);
		else { nextShape = lvl->getRand(); }
	} else {
		shape = lvl->getRand();
		nextShape = lvl->getRand();
	}
    generateShadow();
}

void Player::handleMovement(int moveCol, int moveRow) {
    if(moveCol != 0 && canMove(0, moveCol)) shape->move(moveCol, 0);

    int down = moveRow;
    if(lvl->getLevel() >= 3) down = 1;
    if(isHeavy) down += 2;

    if(down > 0) {
        if(!canMove(down, 0)) dropBlock();
        else shape->move(0, down);
    }

    generateShadow();
}

void Player::generateShadow() {
    delete shadowShape;
    
    shadowShape = new Shape(*shape);
    int dropDistance = calculateDropDistance();
    if (dropDistance > 0) {
        shadowShape->move(0, dropDistance);
    }
}

int Player::calculateDropDistance() {
    if (!shape) return 0;
    
    int distance = 0;
    Shape tempShape(*shape);
    
    while (true) {
        int nextTop = tempShape.getT() + 1;
        int left = tempShape.getL();
        
        if (nextTop + tempShape.getHeight() > 18) break;
        
        bool collision = false;
        for (int i = 0; i < tempShape.getHeight() && !collision; ++i) {
            for (int j = 0; j < tempShape.getWidth() && !collision; ++j) {
                if (tempShape.charAt(j, i) != ' ' && studio.charAt(left + j, nextTop + i) != ' ') {
                    collision = true;
                }
            }
        }
        
        if (collision) break;

        tempShape.move(0, 1);
        distance++;
    }
    
    return distance;
}

void Player::updateTurn(string cmd) { // tested
    if(shape == nullptr) {
		cout << "Shape is null" << endl;
		shape = nextShape;
        if (isRand || lvl->getLevel() == 0) {
			char c;
			
			if (file.get(c)) setNextShape(c);
			else { nextShape = lvl->getRand();  }
		} else {
        	nextShape = lvl->getRand(); 
		}
    }

	// random commands
	if (cmd == "random") isRand = true;
	else if (cmd == "norandom" && (lvl->getLevel() == 3 || lvl->getLevel() == 4)) {
		isRand = false;
		string str;
		cin >> str;
		file.open(str);
		char c;

		if (file.get(c)) { setShape(c); }
		else { shape = lvl->getRand(); }
		if (file.get(c)) { setNextShape(c); }
		else { nextShape = lvl->getRand(); }
        generateShadow();
	}

    //Level commands
    if(cmd == "levelup") {
        setNextLevel();
        return;
    } else if(cmd == "leveldown") {
        setDownLevel();
        return;
    }

	if (cmd == "clockwise") {
		shape->rotateCW();
        generateShadow();
	} else if (cmd == "counterclockwise") {
		shape->rotateCCW();
        generateShadow();
	}

    //Movement commands
    int moveRow = 0, moveCol = 0;
    if(cmd == "left") {
        moveCol = -1; handleMovement(moveCol, moveRow);
    }
    else if(cmd == "right") {
        moveCol = 1; handleMovement(moveCol, moveRow);
    }
    else if(cmd == "down") {
        moveRow = 1; handleMovement(moveCol, moveRow);
    }
    else if(cmd == "drop") dropBlock();

	
	if (lvl->getLevel() == 4) {
		int idx = lvl->dropRandBlock();
		if (idx != -1) {
			cout << "Index: " << idx << endl;
			Shape* rand = new RandShape();
			rand->move(idx, 0);

			Shape* cur = shape, *next = nextShape;
			shape = rand; dropBlock();
			shape = cur; nextShape = next;
            generateShadow();
		}
	}
}

void Player::dropBlock() { // tested
	lvl->setTime(0);

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
    delete shadowShape;
    shadowShape = nullptr;
	shape = nextShape;
	char c;
	if ((lvl->getLevel() == 0 || !(isRand)) && file.is_open() && file.get(c)) {
		nextShape = nullptr;
		setNextShape(c);
	} else {
		nextShape = lvl->getRand();
	} 
    
    while(studio.canRemove() != -1) {
        studio.removeRow();
        totalRowsCleared++;
    }

	isHeavy = false;
	isForce = false;
	isBlind = false;

    generateShadow();
}

int Player::getHighScore() {
    highScore = max(highScore, getScore());
    return highScore; 
}

bool Player::canMove(int r, int c) { // tested
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

std::string Player::renderRow(int n) { // tested
    std::string row_str = "";
    if(isBlind && n >= 2 && n <= 11) {
        for(int i = 0; i < 11; ++i) {
            if(i >= 2 && i <= 8) {
                row_str += "?";
                // std::cout << "?";
            } 
            else {
                row_str += studio.charAt(i, n);
                // std::cout << studio.charAt(i, n);
            }
        }
        return row_str;
    }

    for(int i = 0; i < 11; ++i) {
        if(shape && n >= shape->getT() && n < shape->getT() + shape->getHeight() && i >= shape->getL() && i < shape->getL() + shape->getWidth()) {
            char shapeChar = shape->charAt(i - shape->getL(), n - shape->getT());
            if(shapeChar != ' ') {
                row_str += shapeChar;
                continue;
            }
        }
        else if((shadowShape != nullptr) && (n >= shadowShape->getT()) && (n < shadowShape->getT() + shadowShape->getHeight()) && (i >= shadowShape->getL()) && (i < shadowShape->getL() + shadowShape->getWidth())) {
            char shapeChar = shadowShape->charAt(i - shadowShape->getL(), n - shadowShape->getT());
            if(shapeChar != ' ') {
                row_str += '#';
                continue;
            }
        }
        row_str += studio.charAt(i, n);
    }
    return row_str;
}

std::string Player::renderRowShape(int n) const { // tested
    std::string shape_str = "";
    if(nextShape) {
        for(int i = 0; i < 4; i++) {
            shape_str += nextShape->charAt(i, n);
        }
    } 
    else {
        shape_str += "    ";
        // std::cout << "    ";
    }

    return shape_str;
}

void Player::setShape(char c) {
	if (shape) {
		delete shape; 
    delete shadowShape;
    shadowShape = nullptr;
	}
	
	switch(c) {
		case 'I': {
			shape = new IShape();
			break;
		}

		case 'J': {
			shape = new JShape();
			break;
		}

		case 'L': {
			shape = new LShape();
			break;
		}

		case 'O': {
			shape = new OShape();
			break;
		}

		case 'S': {
			shape = new SShape();
			break;
		}

		case 'Z': {
			shape = new ZShape();
			break;
		}

		case 'T': {
			shape = new TShape();
			break;
		}

		default: {
			shape = lvl->getRand();
			break;
		}
	}
}

void Player::setNextShape(char c) {
	if (nextShape) {
		delete nextShape;
	}

	switch(c) {
		case 'I': {
			nextShape = new IShape();
			break;
		}

		case 'J': {
			nextShape = new JShape();
			break;
		}

		case 'L': {
			nextShape = new LShape();
			break;
		}

		case 'O': {
			nextShape = new OShape();
			break;
		}

		case 'S': {
			nextShape = new SShape();
			break;
		}

		case 'Z': {
			nextShape = new ZShape();
			break;
		}

		case 'T': {
			nextShape = new TShape();
			break;
		}

		default: {
			nextShape = lvl->getRand();
			break;
		}
	}
}
