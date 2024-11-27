#ifndef STUDIO_H
#define STUDIO_H

#include <vector>
//#include "xwindow.h"

class Studio {
    // private members
    std::vector<std::vector<char>> board;
    // Xwindow *window;

    // public members
    public:
        Studio(std::vector<std::vector<char>> b) : board{b} {}
        int canRemove();
        char charAt(int x, int y);
        void removeRow();

        std::vector<std::vector<char>> getBoard() { return board; }
        void setBoard(const std::vector<std::vector<char>>& newBoard) { board = newBoard; }
};

#endif
