#ifndef STUDIO_H
#define STUDIO_H

#include <vector>
#include "xwindow.h"

class Studio {
    // private members
    vector<vector<char>> board;
    Xwindow *window;

    // public members
    public:
        Studio(vector<vector<char>> b) : board{b} {}
        int canRemove();
        char charAt(int x, int y);
        void removeRow();
        void gravity();
};

#endif
