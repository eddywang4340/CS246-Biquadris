#ifndef GAMEPROP_H
#define GAMEPROP_H

#include <map>
#include <string>
#include <fstream>

using namespace std;

class GameProperties {
    map<string, string> properties;
    string file;

public:
    GameProperties(string file = "");
    ~GameProperties();
    string getProp(string prop);
    void setProp(string prop, string value);

    void loadFile(string file);
    void saveFile();
};

#endif
