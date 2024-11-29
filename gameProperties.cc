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
		{"lef", "left"},
        {"left", "left"},
		{"ri", "right"},
		{"rig", "right"},
		{"righ", "right"},
		{"right", "right"},
        {"do", "down"},
		{"dow", "down"},
		{"down", "down"},
        {"dr", "drop"},
		{"dro", "drop"},
		{"drop", "drop"},
		{"i", "I"},
		{"I", "I"},
		{"J", "J"},
		{"j", "J"},
		{"T", "T"},
		{"t", "T"},
		{"O", "O"},
		{"o", "O"},
		{"S", "S"},
		{"s", "S"},
		{"Z", "Z"},
		{"z", "Z"},
		{"L", "L"},
		{"l", "L"},
		{"cl", "clockwise"},
		{"clo", "clockwise"},
		{"cloc", "clockwise"},
		{"clock", "clockwise"},
		{"clockw", "clockwise"},
		{"clockwi", "clockwise"},
		{"clockwis", "clockwise"},
        {"clockwise", "clockwise"},
		{"co", "counterclockwise"},
		{"cou", "counterclockwise"},
		{"coun", "counterclockwise"},
		{"count", "counterclockwise"},
		{"counte", "counterclockwise"},
		{"counter", "counterclockwise"},
		{"counterc", "counterclockwise"},
		{"countercl", "counterclockwise"},
		{"counterclo", "counterclockwise"},
		{"countercloc", "counterclockwise"},
		{"counterclock", "counterclockwise"},
		{"counterclockw", "counterclockwise"},
		{"counterclockwi", "counterclockwise"},
		{"counterclockwis", "counterclockwise"},
		{"counterclockwise", "counterclockwise"},
        {"counterclockwise", "counterclockwise"},
		{"re", "restart"},
		{"res", "restart"},
		{"rest", "restart"},
		{"resta", "restart"},
		{"restar", "restart"},
		{"restart", "restart"},
		{"leveld", "leveldown"},
		{"leveldo", "leveldown"},
		{"leveldow", "leveldown"},
		{"leveldown", "leveldown"},
		{"levelu", "levelup"},
		{"levelup", "levelup"},
		{"ra", "random"},
		{"ran", "random"},
		{"rand", "random"},
		{"rando", "random"},
		{"random", "random"},
		{"n", "norandom"},
		{"no", "norandom"},
		{"nor", "norandom"},
		{"nora", "norandom"},
		{"noran", "norandom"},
		{"norand", "norandom"},
		{"norando", "norandom"},
		{"norandom", "norandom"},
		{"se", "sequence"},
		{"seq", "sequence"},
		{"sequ", "sequence"},
		{"seque", "sequence"},
		{"sequen", "sequence"},
		{"sequenc", "sequence"},
		{"sequence", "sequence"}
    };
    if(file != "") loadFile(file);
}

GameProperties::~GameProperties() {
    saveFile();
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
