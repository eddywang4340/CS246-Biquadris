#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <fstream>
#include "shape.h"

using namespace std;

class Level {
	protected:
		std::vector<char> probability;
		int t;
		int level;

	public:
		Level(int level): t{0}, level{level} {};
		~Level();
		virtual Shape* getRand() = 0;
		virtual int dropRandBlock() = 0;
		Shape* getBlock(char block);
		int getLevel();
		int getTime();
		void setTime(const int& newTime);
		void incrementTime();
};

class LevelZero: public Level {
	public:
		LevelZero();
		Shape *getRand();
		int dropRandBlock() {};
};

class LevelOne: public Level {
	public:
		LevelOne();
		Shape* getRand();
		int dropRandBlock() {};
};

class LevelTwo: public Level {
	public:
		LevelTwo();
		Shape* getRand();
		int dropRandBlock() {};
};

class LevelThree: public Level {
	public:
		LevelThree();
		Shape* getRand();
		int dropRandBlock() {};
};

class LevelFour: public Level {
	public:
		LevelFour();
		Shape* getRand();
		int dropRandBlock();
};

#endif
