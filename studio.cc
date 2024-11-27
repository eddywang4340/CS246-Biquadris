#include "studio.h"
#include "constants.h"
#include "shape.h"
#include <vector>

Studio::Studio() {
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        // populate a blank row
        std::vector<char> row;
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
            if(board[i][j] == ' ') {
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
    int row_remove = canRemove();
    if (row_remove != -1) {
        board.erase(board.begin() + row_remove);

        std::vector<char> empty;
        for(int i = 0; i < GAME_NUM_COL; i++) empty.emplace_back(' ');
        board.insert(board.begin(), empty);
    }
}
