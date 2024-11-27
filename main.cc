#include "level.h"
#include "shape.h"
#include "player.h"
#include "iostream"
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

int main() {
	srand(time(0)); // KEEP THIS
	Player p1 = Player();

	cout << "-----" << endl;
	
	for (int i = 0; i < 5; ++i) {
		p1.dropBlock();

		for (int i = 0; i < 18; ++i) {
			cout << "row" <<endl;
			p1.renderRow(i);
			cout << endl;
		}
	}

	cout << "-----" << endl;
} 