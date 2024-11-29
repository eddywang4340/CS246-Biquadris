#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <fstream>

using namespace std;

class GameProperties {
    map<string, string> properties;
    string file;

public:
    GameProperties(string file = "");
    string getProp(string prop);
    string setProp(string prop, string value);

    void loadFile(string file) { this->file = file; }
    void saveFile();
};

#endif