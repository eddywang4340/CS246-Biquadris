#include "level.h"
#include "shape.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <map>

#include "game.h"

using namespace std;

int main() {
	srand(time(0)); // KEEP THIS
	Game g = Game(4, 4, "", "", true);
	string cmd;

	cout << "----" << endl;

	// for (int i = 0; i < 18; ++i) {
	// 		cout << p1.renderRow(i);
	// 		cout << endl;
	// 	}
	
	// while (cin >> cmd) {
	// 	p1.updateTurn(cmd);

	// 	// for (int i = 0; i < 18; ++i) {
	// 	// 	cout << p1.renderRow(i);
	// 	// 	cout << endl;
	// 	// }

	// 	g.render();

	// 	// cout << "----" << endl;
	// 	// cout << p1.getScore() << endl;
	// 	// cout << "----" << endl;
	// }

	g.update();
}