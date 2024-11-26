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

Shape Level::getBlock(char block) {
	switch(block) {
		case('S'): {
			SShape shape = SShape();
			return shape;
		}
		
		case('Z'): {
			ZShape shape = ZShape();
			return shape;
		}
		
		case('L'): {
			LShape shape = LShape();
			return shape;
		}

		case('I'): {
			IShape shape = IShape();
			return shape;
		}

		case('J'): {
			JShape shape = JShape();
			return shape;
		}

		case('O'): {
			OShape shape = OShape();
			return shape;
		}

		case('T'): {
			TShape shape = TShape();
			return shape;
		}

		default: {
			SShape shape = SShape();
			return shape;
		}
	}
}

LevelOne::LevelOne(): Level(1) {
	probability.insert(probability.end(), {'S', 'Z', 'L', 'L', 'I', 'I', 'J', 'J', 'O', 'O', 'T', 'T'});
}

Shape LevelOne::getRand() {
	int idx = rand() % 12;
	char block = probability[idx];
	return getBlock(block);
}

LevelTwo::LevelTwo(): Level(2) {
	probability.insert(probability.end(), {'S', 'Z', 'L', 'I', 'J', 'O','T'});
}

Shape LevelTwo::getRand() {
	int idx = rand() % 7;
	char block = probability[idx];
	return getBlock(block);
}

LevelThree::LevelThree(string file): Level(3), cmds(file) {
	probability.insert(probability.end(), {'S', 'S', 'Z', 'Z', 'I', 'J', 'O', 'L', 'T'});
}

Shape LevelThree::getRand() {
	int idx = rand() % 9;
	char block = probability[idx];
	return getBlock(block);
} 

Shape LevelThree::getNotRand() {
	cout << "No get random :)" << endl;
}

LevelFour::LevelFour(string file): Level(4), cmds(file) {
	probability.insert(probability.end(), {'S', 'S', 'Z', 'Z', 'I', 'J', 'O', 'L', 'T'});
}

Shape LevelFour::getRand() {
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

Shape LevelFour::getNotRand() {
	cout << "No get random :)" << endl;
}
