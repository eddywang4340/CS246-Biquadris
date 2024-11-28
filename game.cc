#include "game.h"
#include "constants.h"
#include "xwindow.h"
#include <iostream>
#include <iomanip>

Game::Game(int player1_lvl, int player2_lvl, std::string player1_file, std::string player2_file):
    player1{player1_lvl, player2_file}, player2{player2_lvl, player2_file}, turnAcc{0}
{ }

std::string Game::getWinner() {
    // Checks to see which player lost
    if (player1.getLost() == player2.getLost()) {
        // Both players have not lost (not possible for both players to lose) so we compare high scores
        if (player1.getHighScore() > player2.getHighScore()) {
            return "player 1";
        } 
        else if (player2.getHighScore() > player1.getHighScore()) {
            return "player 2";
        } 
        else {
            return "Tie";
        }
    } else if (player1.getLost()) {
        return "player 2";
    } else {
        return "player 1";
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
            // player 1's turn

            // Signals end of turn
            if (command == "drop") {
                turnAcc++;
            }
            player1.updateTurn(command);
        } else {
            // player 2's turn

             // Signals end of turn
            if (command == "drop") {
                turnAcc++;
            }
            player2.updateTurn(command);
        }
    }
}

void Game::render() {
    // each player's level
    std::cout << "Level:" << setw(5) << setfill(' ') << right << player1.getLevel() << "     ";
    std::cout << "Level:" << setw(5) << setfill(' ') << right << player2.getLevel() << std::endl;

    // each player's score
    std::cout << "Score:" << setw(5) << setfill(' ') << right << player1.getScore() << "     ";
    std::cout << "Score:" << setw(5) << setfill(' ') << right << player2.getScore() << std::endl;

    // separator
    std::cout << "-----------     -----------" << std::endl;

    // render row by row
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        player1.renderRow(i);
        std::cout << "     ";
        player2.renderRow(i);
        std::cout << std::endl;
    }

    // separator
    std::cout << "-----------     -----------" << std::endl;

    // render next shape
    std::cout << "Next:           Next:      " << std::endl;
    for (int i = 0; i < SHAPE_GRID_NUM_ROW; ++i) {
        player1.renderRowShape(i);
        std::cout << "            ";
        player2.renderRowShape(i);
        std::cout << std::endl;
    }
}

void Game::restart() {
    // Update both players' totalRowsCleared
    player1.updateRowsCleared(0);
    player2.updateRowsCleared(0);

    // Set turnAcc to 0
    turnAcc = 0;

    // Reset player's game boards
    player1.resetBoard();
    player2.resetBoard();
}

void Game::initializeGraphics() {
    window(Xwindow{2 * GAME_NUM_COL + 10, GAME_NUM_ROW + 10});
}

void Game::graphicRender() {
    // display each player's level
    window.drawString(0, 0, "Level: " + std::to_string(player1.getLevel())); // Player 1's level
    window.drawString(21, 0, "Level: " + std::to_string(player2.getLevel())); // Player 2's level

    // display each player's score
    window.drawString(0, 1, "Score: " + std::to_string(player1.getScore())); // Player 1's score
    window.drawString(21, 1, "Score: " + std::to_string(player2.getScore())); // Player 2's score

    // Render board
}
