#include "studio.h"
#include "constants.h"
#include "shape.h"
#include <vector>

Studio::Studio() {
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        // populate a blank row
        std::vector<c> row;
        for (int j = 0; j < GAME_NUM_COL; ++j) {
            row.emplace_back(' ');
        }
        board.emplace_back(row);
    }
}

int Studio::canRemove() {
    bool canRemove;
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        canRemove = true;
        for (int j = 0; j < GAME_NUM_COL; ++j) {
            if board[i][j] == ' ' {
                canRemove = false;
                break;
            }
        }
        if (canRemove) {
            return i;
        }
    }
    return -1;
}

char Studio::charAt(int x, int y) {
    return board[y][x];
}

void Studio::removeRow() {
    row_remove = canRemove();
    if (row_remove != -1) {
        for (int i = 0; i < GAME_NUM_COL; ++i) {
            board[row_remove][i] = ' ';
        }
    }
}
