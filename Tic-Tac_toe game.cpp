#include <iostream>
#include <vector>
#include <limits>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    
    // Clear input buffer after invalid input
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    // Constructor - initialize the game
    TicTacToe() {
        initializeBoard();
        currentPlayer = 'X';
    }

    // Create a 3x3 grid as the game board
    void initializeBoard() {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    }

    // Show the current state of the board
    void displayBoard() {
        std::cout << "\n   |   |   " << std::endl;
        std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
        std::cout << "___|___|___" << std::endl;
        std::cout << "   |   |   " << std::endl;
        std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
        std::cout << "___|___|___" << std::endl;
        std::cout << "   |   |   " << std::endl;
        std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;
        std::cout << "   |   |   " << std::endl;
        
        std::cout << "\nPositions:" << std::endl;
        std::cout << " 1 | 2 | 3 " << std::endl;
        std::cout << "___|___|___" << std::endl;
        std::cout << " 4 | 5 | 6 " << std::endl;
        std::cout << "___|___|___" << std::endl;
        std::cout << " 7 | 8 | 9 " << std::endl;
        std::cout << std::endl;
    }

    // Prompt the current player to enter their move
    bool playerInput() {
        int position;
        std::cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        
        if (!(std::cin >> position)) {
            clearInput();
            std::cout << "Invalid input! Please enter a number between 1 and 9." << std::endl;
            return false;
        }

        if (position < 1 || position > 9) {
            std::cout << "Invalid position! Please enter a number between 1 and 9." << std::endl;
            return false;
        }

        // Convert position to row and column
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        // Check if position is already taken
        if (board[row][col] != ' ') {
            std::cout << "Position already taken! Please choose another position." << std::endl;
            return false;
        }

        // Update board with the player's move
        board[row][col] = currentPlayer;
        return true;
    }

    // Check if the current player has won
    bool checkForWin() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == currentPlayer && board[1][j] == currentPlayer && board[2][j] == currentPlayer) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
            return true;
        }

        return false;
    }

    // Determine if the game is a draw
    bool checkForDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false; // Game is not a draw if there are empty spaces
                }
            }
        }
        return true; // All spaces are filled and no winner
    }

    // Alternate turns between "X" and "O" players
    void switchPlayers() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Show the result of the game (win, draw, or ongoing)
    void displayResult(bool won, bool draw) {
        displayBoard();
        
        if (won) {
            std::cout << "🎉 Congratulations! Player " << currentPlayer << " wins!" << std::endl;
        } else if (draw) {
            std::cout << "🤝 It's a draw! Good game both players!" << std::endl;
        }
    }

    // Ask if the players want to play another game
    bool playAgain() {
        char choice;
        std::cout << "\nDo you want to play another game? (y/n): ";
        
        while (true) {
            if (std::cin >> choice) {
                choice = std::tolower(choice);
                if (choice == 'y') {
                    initializeBoard();
                    currentPlayer = 'X';
                    return true;
                } else if (choice == 'n') {
                    return false;
                } else {
                    std::cout << "Please enter 'y' for yes or 'n' for no: ";
                }
            } else {
                clearInput();
                std::cout << "Invalid input! Please enter 'y' or 'n': ";
            }
        }
    }

    // Main game loop
    void playGame() {
        std::cout << "========================================" << std::endl;
        std::cout << "        Welcome to Tic-Tac-Toe!" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Players: X and O" << std::endl;
        std::cout << "Enter positions 1-9 to make your move" << std::endl;
        std::cout << "========================================" << std::endl;

        do {
            bool gameOngoing = true;
            
            while (gameOngoing) {
                displayBoard();
                
                // Get player input
                if (playerInput()) {
                    // Check for win
                    if (checkForWin()) {
                        displayResult(true, false);
                        gameOngoing = false;
                    }
                    // Check for draw
                    else if (checkForDraw()) {
                        displayResult(false, true);
                        gameOngoing = false;
                    }
                    // Switch players for next turn
                    else {
                        switchPlayers();
                    }
                }
                // If invalid input, stay with current player and ask again
            }
            
        } while (playAgain());

        std::cout << "\nThank you for playing Tic-Tac-Toe! Goodbye!" << std::endl;
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}