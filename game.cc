#include "game.h"
#include "constants.h"
#include <iostream>
#include <iomanip>

std::string Game::getWinner() {
    // Checks to see which player lost
    if (Player1.getLost() == Player2.getLost()) {
        // Both players have not lost (not possible for both players to lose) so we compare high scores
        if (Player1.getHighScore() > Player2.getHighScore()) {
            return "Player 1";
        } else if (Player2.getHighScore() > Player1.getHighScore()) {
            return "Player 2";
        } else {
            return "Tie";
        }
    } else if (Player1.getLost()) {
        return "Player 2";
    } else {
        return "Player 1";
    }
}

void Game::update() {
    while (true) {
        std::string command;
        std::cin >> command;
        if (std::cin.eof() || command == "restart") {
            // reached end of file or restart, end the game
            std::string winner = getWinner();
            std::cout << winner << " has won!" << std::endl;
            if (command == "restart") {
                // restart game
                restart();
            }
            break;
        }

        // Checking which player's turn it is
        if (turnAcc % 2 == 0) {
            // Player 1's turn

            // Signals end of turn
            if (command == "drop") {
                turnAcc++;
            }
            Player1.updateTurn(command);
        } else {
            // Player 2's turn

             // Signals end of turn
            if (command == "drop") {
                turnAcc++;
            }
            Player2.updateTurn(command);
        }
    }
}

void Game::render() {
    // each player's level
    std::cout << "Level:" << setw(5) << setfill(' ') << right << Player1.getLevel() << "     ";
    std::cout << "Level:" << setw(5) << setfill(' ') << right << Player2.getLevel() << std::endl;

    // each player's score
    std::cout << "Score:" << setw(5) << setfill(' ') << right << Player1.getScore() << "     ";
    std::cout << "Score:" << setw(5) << setfill(' ') << right << Player2.getScore() << std::endl;

    // separator
    std::cout << "-----------     -----------" << std::endl;

    // render row by row
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        Player1.renderRow(i);
        std::cout << "     ";
        Player2.renderRow(i);
        std::cout << std:endl;
    }

    // separator
    std::cout << "-----------     -----------" << std::endl;

    // render next shape
    std::cout "Next:           Next:      " << std::endl;
    for (int i = 0; i < SHAPE_GRID_NUM_ROW; ++i) {
        Player1.renderRowShape(i);
        std::cout << "            ";
        Player2.renderRowShape(i);
        std::cout << std::endl;
    }

}

void Game::restart() {
    // Update both Players' totalRowsCleared
    Player1.updateRowsCleared(0);
    Player2.updateRowsCleared(0);

    // Set turnAcc to 0
    turnAcc = 0;

    // Reset Player's game boards
    Player1.resetBoard();
    Player2.resetBoard();
}
