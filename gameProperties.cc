#include "gameProperties.h"
#include <iostream>

void GameProperties::loadFile(string file) {
    this->file = file;

    ifstream fs(this->file); string row;
    while(getline(fs, row)) {
        string key = row.substr(0, row.find(' '));
        string value = row.substr(row.find(' ') + 1);
        properties[key] = value;
    }
}

GameProperties::GameProperties(string file) : file{file} {
    properties = {
        {"l", "left"},
        {"r", "right"},
        {"d", "down"},
        {"D", "drop"},
        {"c", "clockwise"},
        {"cc", "counterclockwise"},

        {"left", "left"},
        {"right", "right"},
        {"down", "down"},
        {"drop", "drop"},
        {"clockwise", "clockwise"},
        {"counterclockwise", "counterclockwise"}
    };
    if(file != "") loadFile(file);
}

string GameProperties::getProp(string prop) {
    if(properties.contains(prop)) return properties[prop];
    return "no cmd";
}

void GameProperties::setProp(string prop, string value) {
    properties[prop] = value;
}

void GameProperties::saveFile() {
    ofstream ofs(file);
    for(auto i : properties) ofs << i.first << " " << i.second << endl;
}
