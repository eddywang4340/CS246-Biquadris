#include "level.h"
#include "shape.h"
#include "player.h"
#include "iostream"
#include <cstdlib>
#include <vector>
#include <ctime>

#include "game.h"

using namespace std;

int main() {
	srand(time(0)); // KEEP THIS
	Player p1 = Player();
	string cmd;

	cout << "----" << endl;
	
	while (cin >> cmd) {
		p1.updateTurn(cmd);

		for (int i = 0; i < 18; ++i) {
			p1.renderRow(i);
			cout << endl;
		}

		cout << "----" << endl;
	}
} 