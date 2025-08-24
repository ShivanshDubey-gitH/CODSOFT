#include <iostream>
#include <limits>
#include <iomanip>

class Calculator {
private:
    double num1, num2;
    char operation;

    // Clear input buffer after invalid input
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get a valid number from user
    bool getNumber(double& number, const std::string& prompt) {
        std::cout << prompt;
        if (std::cin >> number) {
            return true;
        } else {
            clearInput();
            std::cout << "Invalid input! Please enter a valid number." << std::endl;
            return false;
        }
    }

    // Get a valid operation from user
    bool getOperation() {
        std::cout << "Choose an operation (+, -, *, /): ";
        if (std::cin >> operation) {
            if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
                return true;
            } else {
                std::cout << "Invalid operation! Please choose +, -, *, or /" << std::endl;
                return false;
            }
        } else {
            clearInput();
            std::cout << "Invalid input! Please enter an operation." << std::endl;
            return false;
        }
    }

    // Perform the calculation and display result
    void performCalculation() {
        double result;
        bool validOperation = true;

        switch (operation) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    std::cout << "Error: Division by zero is not allowed!" << std::endl;
                    validOperation = false;
                }
                break;
            default:
                std::cout << "Error: Unknown operation!" << std::endl;
                validOperation = false;
        }

        if (validOperation) {
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "\nResult: " << num1 << " " << operation << " " << num2 << " = " << result << std::endl;
        }
    }

    // Ask if user wants to continue
    bool askContinue() {
        char choice;
        std::cout << "\nDo you want to perform another calculation? (y/n): ";
        
        while (true) {
            if (std::cin >> choice) {
                choice = std::tolower(choice);
                if (choice == 'y') {
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

public:
    // Display welcome message
    void displayWelcome() {
        std::cout << "========================================" << std::endl;
        std::cout << "        Welcome to Calculator!" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "This calculator supports:" << std::endl;
        std::cout << "  + Addition" << std::endl;
        std::cout << "  - Subtraction" << std::endl;
        std::cout << "  * Multiplication" << std::endl;
        std::cout << "  / Division" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    // Main calculator loop
    void run() {
        displayWelcome();

        do {
            std::cout << "\n--- New Calculation ---" << std::endl;
            
            // Get first number
            while (!getNumber(num1, "Enter the first number: ")) {
                // Keep asking until valid input
            }

            // Get operation
            while (!getOperation()) {
                // Keep asking until valid input
            }

            // Get second number
            while (!getNumber(num2, "Enter the second number: ")) {
                // Keep asking until valid input
            }

            // Perform calculation and display result
            performCalculation();

        } while (askContinue());

        std::cout << "\nThank you for using the calculator! Goodbye!" << std::endl;
    }
};

int main() {
    Calculator calc;
    calc.run();
    return 0;
}