#include "game.h"
#include "constants.h"
#include "xwindow.h"
#include "shape.h"
#include <iostream>
#include <iomanip>

Game::Game(int player1_lvl, int player2_lvl, std::string player1_file, std::string player2_file, bool isGraphics):
    player1(player1_lvl, player1_file), player2(player2_lvl, player2_file), turnAcc{0}, isGraphics{isGraphics}, gameProps{"gameProps.txt"}
{ 
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        // populate a blank row
        std::vector<char> row1;
        std::vector<char> row2;
        for (int j = 0; j < GAME_NUM_COL; ++j) {
            row1.emplace_back(' ');
            row2.emplace_back(' ');
        }
        player1_board.emplace_back(row1);
        player2_board.emplace_back(row2);
    }
    // cout << player1_board[0].size() << endl;
    // cout << player2_board[0].size() << endl;
    initializeGraphics();
	render();
}

Game::~Game() { if (window) delete window; }

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
    int multiplier = 1;
    while (true) {
        if (turnAcc % 2 == 0) cout << "Player 1's turn:" << endl;
        else {
            cout << "Player 2's turn:" << endl;
        }
        // if player has positive dropNum (don't prompt user for command, just drop)

        // if it is player 1's turn then do this
        if (turnAcc % 2 == 0) {
            if (player1.getDropNum() > 0) {
                // decrement dropNum
                player1.decrementDropNum();
                player1.dropBlock();
                turnAcc++;
                render();
                continue;
            }
        } else {
            if (player2.getDropNum() > 0) {
                // decrement
                player2.decrementDropNum();
                player2.dropBlock();
                turnAcc++;
                render();
                continue;
            }
        }

        std::string command;
        std::cin >> command;

        multiplier = 1;
        int num_digits = 0;
        while (isdigit(command[0])) {
            int digit = command[0] - '0';
            num_digits++;
            if (num_digits > 1) {
                // multi-digit case
                multiplier *= 10;
                multiplier += digit;
            } else {
                // single digit case
                multiplier = digit;
            }
            // remove the first digit from cmd
            command.erase(command.begin());
        }

        if(gameProps.getProp(command) != "") {
            command = gameProps.getProp(command);
        }

        if (std::cin.eof() || command == "restart") {
            // reached end of file or restart, end the game
            std::string winner = getWinner();
            if (winner != "Tie") std::cout << winner << " has won!" << std::endl;
            else { cout << winner << endl; }

            if (command == "restart") {
                restart();
            }

			if (std::cin.eof()) break;
        }

        // Checking which player's turn it is
        if (turnAcc % 2 == 0) {
			int prev = player1.getRowsCleared();

			if (command == "sequence") {
				string file;
				cin >> file;
				ifstream f{file};
				string cmd;

				while (getline(f, cmd)) {
					cout << cmd << endl;
					player1.updateTurn(cmd, 1);
					if (cmd == "drop") turnAcc++;
					render();
				}

			} else {
                    player1.updateTurn(command, multiplier);

				if (command == "drop") turnAcc++;

            render();

				// Signals end of turn
				if (command == "drop") {
					if (player1.getRowsCleared() - prev >= 2) {
						cout << "Player 1 gets a powerup! Would you like to apply heavy, force or blind?" << endl;
						string cmd;
						cin >> cmd;

						if (cmd == "heavy") player2.setHeavy();
						else if (cmd == "force") {
							cout << "What shape do you want the opponent to have next? (I, J, L, O, S, Z, T)" << endl;
							char shape;
							cin >> shape;
							player2.setShape(shape);
							
						}
						else { player2.setBlind(); }
						render();
					}
				}
			}

			if (player1.getLost()) {
				cout << "Player 2 won" << endl;
				restart();
			}

        } else {
			int prev = player2.getRowsCleared();

			if (command == "sequence") {
				string file;
				cin >> file;
				ifstream f{file};
				string cmd;

				while (getline(f, cmd)) {
					cout << cmd << endl;
					player2.updateTurn(cmd, 1);
					if (cmd == "drop") turnAcc++;
					render();
				}

			} else {
				player2.updateTurn(command, multiplier);

				if (command == "drop") turnAcc++;

            render();

				// Signals end of turn
				if (command == "drop") {
					if (player2.getRowsCleared() - prev >= 2) {
						cout << "Player 2 gets a powerup! Would you like to apply heavy, force or blind?" << endl;
						string cmd;
						cin >> cmd;

						if (cmd == "heavy") player1.setHeavy();
						else if (cmd == "force") {
							cout << "What shape do you want the opponent to have next? (I, J, L, O, S, Z, T)" << endl;
							char shape;
							cin >> shape;
							player1.setShape(shape);
						}
						else { player1.setBlind(); }
						render();
					}
				}
			}

			if (player2.getLost()) {
				cout << "Player 1 won" << endl;
				restart();
			}
        }
    }
}

void Game::render() {
    if (isGraphics) {
        // render in graphical display
        // display each player's level
        window->fillRectangle(0, 1 * 20 - 15, 100, 20, Xwindow::White);
        window->drawString(0, 1 * 20, "Level: " + std::to_string(player1.getLevel())); // Player 1's level
        window->fillRectangle(21 * 20, 1 * 20 - 15, 100, 20, Xwindow::White);
        window->drawString(21 * 20, 1 * 20, "Level: " + std::to_string(player2.getLevel())); // Player 2's level

        // display each player's score
        window->fillRectangle(0, 2 * 20 - 15, 100, 20, Xwindow::White);
        window->drawString(0, 2 * 20, "Score: " + std::to_string(player1.getScore())); // Player 1's score
        window->fillRectangle(21 * 20, 2 * 20 - 15, 100, 20, Xwindow::White);
        window->drawString(21 * 20, 2 * 20, "Score: " + std::to_string(player2.getScore())); // Player 2's score

        // display each player's highscore
        window->fillRectangle(0, 3 * 20 - 15, 100, 20, Xwindow::White);
        window->drawString(0, 3 * 20, "Highscore: " + std::to_string(player1.getHighScore())); // Player 1's highscore
        window->fillRectangle(21 * 20, 3 * 20 - 15, 100, 20, Xwindow::White);
        window->drawString(21 * 20, 3 * 20, "Highscore: " + std::to_string(player2.getHighScore())); // Player 2's highscore

        int colour1 = 0;
        int colour2 = 0;
        // Render board
        for (int i = 0; i < GAME_NUM_ROW; ++i) {
            // getting string from board
            std::string row1 = player1.renderRow(i);
            std::string row2 = player2.renderRow(i);
            if (row1.size() != GAME_NUM_COL || row2.size() != GAME_NUM_COL) {
                std::cout << "Error: Render rows have unexpected size.\n";
                return;
            }
            for (int j = 0; j < GAME_NUM_COL; ++j) {
                // logic: only render the board if it is different then previous
                if (player1_board[i][j] != row1[j] /*&& ((turnAcc % 2 == 0) || turnAcc == 0)*/) {
                    // check character for player 1 and display
                    colour1 = CHAR_TO_COLOUR[row1[j]];
                    // if (colour1 != 0) {
                    //     window->fillRectangle(j * 20, (i + 3) * 20, 20, 20, colour1);
                    //     player1_board[j][i] = row1[j];
                    // }
                    window->fillRectangle(j * 20, (i + 4) * 20, 20, 20, colour1);
                    player1_board[i][j] = row1[j];
                }
                if (player2_board[i][j] != row2[j] /*&& (turnAcc % 2 != 0 || turnAcc == 0)*/) {
                    // check character for player 2 and display
                    colour2 = CHAR_TO_COLOUR[row2[j]];
                    // if (colour2 != 0) {
                    //     window->fillRectangle((j + 21) * 20, (i + 3) * 20, 20, 20, colour2);
                    //     player2_board[j][i] = row2[j];
                    // }
                    window->fillRectangle((j + 21) * 20, (i + 4) * 20, 20, 20, colour2);
                        player2_board[i][j] = row2[j];
                }
            }
        }

        int colour1_shape = 0;
        int colour2_shape = 0;
        // render next shape
        window->drawString(0 * 20, (GAME_NUM_ROW + 5) * 20, "Next:");
        window->drawString(21 * 20, (GAME_NUM_ROW + 5) * 20, "Next:");
        for (int i = 0; i < SHAPE_GRID_NUM_ROW; ++i) {
            std::string shape_row1 = player1.renderRowShape(i);
            std::string shape_row2 = player2.renderRowShape(i);
            for (int j = 0; j < SHAPE_GRID_NUM_COL; ++j) {
                // check character for player 1 and display
                colour1_shape = CHAR_TO_COLOUR[shape_row1[j]];
                window->fillRectangle(j * 20, (i + GAME_NUM_ROW + 6) * 20, 20, 20, colour1_shape);

                // check character for player 2 and display
                colour2_shape = CHAR_TO_COLOUR[shape_row2[j]];
                window->fillRectangle((j + 21) * 20, (i + GAME_NUM_ROW + 6) * 20, 20, 20, colour2_shape);
            }
        }
    }

    // render in text format
    // each player's level
    std::cout << "Level:" << setw(7) << setfill(' ') << right << player1.getLevel() << "    ";
    std::cout << "Level:" << setw(7) << setfill(' ') << right << player2.getLevel() << std::endl;

    // each player's score
    std::cout << "Score:" << setw(7) << setfill(' ') << right << player1.getScore() << "    ";
    std::cout << "Score:" << setw(7) << setfill(' ') << right << player2.getScore() << std::endl;

    // highscore
    gameProps.setProp("highscore1", to_string(player1.getHighScore()));
    gameProps.setProp("highscore2", to_string(player2.getHighScore()));
    std::cout << "Highscore:" << setw(3) << setfill(' ') << right << player1.getHighScore() << "    ";
    std::cout << "Highscore:" << setw(3) << setfill(' ') << right << player2.getHighScore() << std::endl;

    // separator
    std::cout << "-----------      -----------" << std::endl;

    // render row by row
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        std::cout << player1.renderRow(i);
        std::cout << "      ";
        std::cout << player2.renderRow(i);
        std::cout << std::endl;
    }

    // separator
    std::cout << "-----------     -----------" << std::endl;

    // render next shape
    std::cout << "Next:           Next:      " << std::endl;
    for (int i = 0; i < SHAPE_GRID_NUM_ROW; ++i) {
        std::cout << player1.renderRowShape(i);
        std::cout << "            ";
        std::cout << player2.renderRowShape(i);
        std::cout << std::endl;
    }

    // if (turnAcc % 2 == 0) cout << "Player 1's turn:" << endl;
    // else {
    //     cout << "Player 2's turn:" << endl;
    // }
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

    // Reset player1_board and player2_board
    player1_board.clear();
    player2_board.clear();
    for (int i = 0; i < GAME_NUM_ROW; ++i) {
        // populate a blank row
        std::vector<char> row1;
        std::vector<char> row2;
        for (int j = 0; j < GAME_NUM_COL; ++j) {
            row1.emplace_back(' ');
            row2.emplace_back(' ');
        }
        player1_board.emplace_back(row1);
        player2_board.emplace_back(row2);
    }

    if (isGraphics) {
        // clear the graphical board
        delete window;
        initializeGraphics();
    }

	render();
}

void Game::initializeGraphics() {
    if (isGraphics) {
        window = new Xwindow {(2 * GAME_NUM_COL + 10) * 20, (GAME_NUM_ROW + 10) * 20};
    }
}
