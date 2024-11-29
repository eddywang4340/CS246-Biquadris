#include "level.h"
#include "shape.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

Level::~Level() {
	t = 0;
	probability.clear();
}

int Level::getTime() { return t; }

void Level::setTime(const int& newTime) { t = newTime; }

void Level::incrementTime() { t++; }

int Level::getLevel() { return level; }

Shape* Level::getBlock(char block) {
	switch(block) {
		case('S'): {
			Shape* shape = new SShape();
			return shape;
		}
		
		case('Z'): {
			Shape* shape = new ZShape();
			return shape;
		}
		
		case('L'): {
			Shape* shape = new LShape();
			return shape;
		}

		case('I'): {
			Shape* shape = new IShape();
			return shape;
		}

		case('J'): {
			Shape* shape = new JShape();
			return shape;
		}

		case('O'): {
			Shape* shape = new OShape();
			return shape;
		}

		case('T'): {
			Shape* shape = new TShape();
			return shape;
		}

		default: {
			SShape* shape = new SShape();
			return shape;
		}
	}
}

LevelZero::LevelZero(): Level(0) {
	probability.insert(probability.end(), {'S', 'Z', 'L', 'L', 'I', 'I', 'J', 'J', 'O', 'O', 'T', 'T'});
}

Shape* LevelZero::getRand() {
	int idx = rand() % 12;
	char block = probability[idx];
	return getBlock(block);
}

LevelOne::LevelOne(): Level(1) {
	probability.insert(probability.end(), {'S', 'Z', 'L', 'L', 'I', 'I', 'J', 'J', 'O', 'O', 'T', 'T'});
}

Shape* LevelOne::getRand() {
	int idx = rand() % 12;
	char block = probability[idx];
	return getBlock(block);
}

LevelTwo::LevelTwo(): Level(2) {
	probability.insert(probability.end(), {'S', 'Z', 'L', 'I', 'J', 'O','T'});
}

Shape* LevelTwo::getRand() {
	int idx = rand() % 7;
	char block = probability[idx];
	return getBlock(block);
}

LevelThree::LevelThree(): Level(3) {
	probability.insert(probability.end(), {'S', 'S', 'Z', 'Z', 'I', 'J', 'O', 'L', 'T'});
}

Shape* LevelThree::getRand() {
	int idx = rand() % 9;
	char block = probability[idx];
	return getBlock(block);
} 

LevelFour::LevelFour(): Level(4) {
	probability.insert(probability.end(), {'S', 'S', 'Z', 'Z', 'I', 'J', 'O', 'L', 'T'});
}

Shape* LevelFour::getRand() {
	int idx = rand() % 9;
	char block = probability[idx];
	return getBlock(block);
} 

int LevelFour::dropRandBlock() {
	t++;

	if (t == 5) {
		t = 0;
		int idx = rand() % 11;
		return idx;
	}

	return -1;
}
