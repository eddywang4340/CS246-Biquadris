#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "game.h"

using namespace std;

int main() {
	srand(time(0)); // KEEP THIS

    Game game(0, 0, "", "");

	LevelOne l1 = LevelOne();
	Shape* s = l1.getRand();

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			cout << s->charAt(i, j) << ' ';
		}
		cout << endl;
	}

	cout << "----" << endl;
} 