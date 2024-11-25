#include "game.h"
#include <iostream>
#include <iomanip>

const int GAME_NUM_ROW = 18;
const int GAME_NUM_COL = 11;
const int SHAPE_GRID_NUM_ROW = 4;

std::string Game::getWinner() {

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

}
