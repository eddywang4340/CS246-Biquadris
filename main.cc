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
	int l1, l2;
	cout << "Player 1, choose your level: (0-4)" << endl;
	cin >> l1;
	cout << "Player 2, choose your level: (0-4)" << endl;
	cin >> l2;
	Game g = Game(l1, l2, "", "", false);
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