#include <iostream>
#include <random>
#include <limits>
#include <string>

class NumberGuessingGame {
private:
    int targetNumber;
    int attempts;
    int minRange;
    int maxRange;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    // Constructor initializes the game with a specified range
    NumberGuessingGame(int min = 1, int max = 100) 
        : attempts(0), minRange(min), maxRange(max), gen(rd()), dis(min, max) {
        generateNewNumber();
    }

    // Generate a new random number within the specified range
    void generateNewNumber() {
        targetNumber = dis(gen);
        attempts = 0;
    }

    // Display welcome message and game instructions
    void displayWelcome() {
        std::cout << "\n=================================" << std::endl;
        std::cout << "  Welcome to Number Guessing Game!" << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << "I'm thinking of a number between " << minRange 
                  << " and " << maxRange << "." << std::endl;
        std::cout << "Can you guess what it is?" << std::endl;
        std::cout << "Enter your guess (or 'quit' to exit): " << std::endl;
    }

    // Get user input with validation
    bool getUserInput(int& guess) {
        std::string input;
        std::cout << "\nAttempt #" << (attempts + 1) << ": ";
        
        if (!(std::cin >> input)) {
            // Handle input stream failure
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number or 'quit'." << std::endl;
            return false;
        }

        // Check if user wants to quit
        if (input == "quit" || input == "exit" || input == "q") {
            return false;
        }

        // Try to convert string to integer
        try {
            guess = std::stoi(input);
            
            // Check if guess is within valid range
            if (guess < minRange || guess > maxRange) {
                std::cout << "Please enter a number between " << minRange 
                          << " and " << maxRange << "." << std::endl;
                return false;
            }
            
            attempts++;
            return true;
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input! Please enter a valid number or 'quit'." << std::endl;
            return false;
        } catch (const std::out_of_range& e) {
            std::cout << "Number too large! Please enter a number between " 
                      << minRange << " and " << maxRange << "." << std::endl;
            return false;
        }
    }

    // Process the user's guess and provide feedback
    bool processGuess(int guess) {
        if (guess == targetNumber) {
            std::cout << "\n🎉 Congratulations! You guessed it!" << std::endl;
            std::cout << "The number was " << targetNumber << std::endl;
            std::cout << "It took you " << attempts << " attempt(s)." << std::endl;
            
            // Provide performance feedback
            if (attempts == 1) {
                std::cout << "Amazing! You got it on the first try!" << std::endl;
            } else if (attempts <= 3) {
                std::cout << "Excellent! Very few attempts needed!" << std::endl;
            } else if (attempts <= 7) {
                std::cout << "Good job! That's a reasonable number of attempts." << std::endl;
            } else {
                std::cout << "You got there in the end! Practice makes perfect." << std::endl;
            }
            
            return true; // Game won
        } else if (guess < targetNumber) {
            std::cout << "Too low! Try a higher number." << std::endl;
            
            // Provide additional hints for very close guesses
            int difference = targetNumber - guess;
            if (difference <= 5) {
                std::cout << "You're getting close!" << std::endl;
            } else if (difference <= 10) {
                std::cout << "Getting warmer..." << std::endl;
            }
        } else {
            std::cout << "Too high! Try a lower number." << std::endl;
            
            // Provide additional hints for very close guesses
            int difference = guess - targetNumber;
            if (difference <= 5) {
                std::cout << "You're getting close!" << std::endl;
            } else if (difference <= 10) {
                std::cout << "Getting warmer..." << std::endl;
            }
        }
        
        return false; // Game continues
    }

    // Ask if player wants to play again
    bool askPlayAgain() {
        std::string input;
        std::cout << "\nWould you like to play again? (y/n): ";
        
        while (true) {
            std::cin >> input;
            
            // Convert to lowercase for easier comparison
            for (auto& c : input) {
                c = std::tolower(c);
            }
            
            if (input == "y" || input == "yes") {
                generateNewNumber();
                return true;
            } else if (input == "n" || input == "no") {
                return false;
            } else {
                std::cout << "Please enter 'y' for yes or 'n' for no: ";
            }
        }
    }

    // Main game loop
    void playGame() {
        displayWelcome();
        
        bool gameWon = false;
        int guess;
        
        while (!gameWon) {
            if (getUserInput(guess)) {
                gameWon = processGuess(guess);
            } else {
                // User wants to quit or invalid input
                if (std::cin.eof()) {
                    break; // Handle Ctrl+D or EOF
                }
                // For invalid input, continue the loop
                continue;
            }
        }
        
        if (gameWon && askPlayAgain()) {
            playGame(); // Recursive call for new game
        }
    }

    // Display goodbye message
    void displayGoodbye() {
        std::cout << "\nThanks for playing the Number Guessing Game!" << std::endl;
        std::cout << "Goodbye! 👋" << std::endl;
    }
};

// Function to get custom range from user (optional feature)
bool getCustomRange(int& min, int& max) {
    std::string input;
    std::cout << "Would you like to set a custom range? (y/n, default is 1-100): ";
    std::cin >> input;
    
    for (auto& c : input) {
        c = std::tolower(c);
    }
    
    if (input == "y" || input == "yes") {
        std::cout << "Enter minimum number: ";
        while (!(std::cin >> min)) {
            std::cout << "Invalid input! Please enter a valid number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cout << "Enter maximum number: ";
        while (!(std::cin >> max) || max <= min) {
            if (max <= min) {
                std::cout << "Maximum must be greater than minimum (" << min << "). Try again: ";
            } else {
                std::cout << "Invalid input! Please enter a valid number: ";
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        return true;
    }
    
    return false;
}

int main() {
    std::cout << "🎲 Number Guessing Game 🎲" << std::endl;
    
    int minRange = 1, maxRange = 100;
    
    // Optional: Allow user to set custom range
    if (getCustomRange(minRange, maxRange)) {
        std::cout << "Great! Playing with range " << minRange << " to " << maxRange << std::endl;
    }
    
    // Create game instance and start playing
    NumberGuessingGame game(minRange, maxRange);
    game.playGame();
    game.displayGoodbye();
    
    return 0;
}