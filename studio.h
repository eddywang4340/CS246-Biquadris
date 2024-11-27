#ifndef STUDIO_H
#define STUDIO_H

// #include "xwindow.h"
#include <vector>

class Studio {
    // private members
    vector<vector<char>> board;
    // Xwindow *window;

    // public members
    public:
        Studio();
        int canRemove();
        char charAt(int x, int y);
        void removeRow();
};

#endif
