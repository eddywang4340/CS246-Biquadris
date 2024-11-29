#include "level.h"
#include "shape.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <map>
#include <string>

#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
    int seed = 0, level = 0; 
    bool graphics = true;
    string f1 = "sequence1.txt", f2 = "sequence2.txt";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-seed") {
            seed = stoi(argv[i+1]);
        }

        if (arg == "-text") {
            graphics = false;
        }

        if (arg == "-startlevel") {
            level = stoi(argv[i+1]);
        }

        if (arg == "-scriptfile1") {
            f1 = argv[i+1];
        }

        if (arg == "-scriptfile2") {
            f2 = argv[i+1];
        }
    }

    cout << "Seed: " << seed << endl;
    cout << "Graphics: " << graphics << endl;
    cout << "File 1: " << f1 << endl;
    cout << "File 2: " << f2 << endl;
    cout << "Level: " << level << endl;

    srand(seed);
    Game g(level, level, f1, f2, graphics);
    string cmd;

    cout << "----" << endl;

    g.update();
}