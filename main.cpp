#include <iostream>
#include <string>
#include <regex>

// Function to remove all spaces from a string
std::string remove_spaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}

int main() {
    std::string equation;
    std::cout << "Enter an equation (e.g., 10x+1024=1034): ";
    std::getline(std::cin, equation);

    // Remove all spaces from the input equation
    equation = remove_spaces(equation);

    // Regex pattern to handle different formats and orders
    std::regex improved_expr("([+-]?\\d*)x([+-]\\d*)=([+-]?\\d+)|([+-]?\\d+)([+-]\\d*)x=([+-]?\\d+)");
    std::smatch matches;
    if (std::regex_search(equation, matches, improved_expr)) {
        int a, b, c;
        if (!matches[1].str().empty() || !matches[2].str().empty()) { // First pattern match
            a = (matches[1].str().empty() || matches[1].str() == "+") ? 1 : (matches[1].str() == "-") ? -1 : std::stoi(matches[1].str());
            b = matches[2].str().empty() ? 0 : std::stoi(matches[2].str());
            c = std::stoi(matches[3].str());
        } else { // Second pattern match
            b = std::stoi(matches[4].str());
            a = (matches[5].str().empty() || matches[5].str() == "+") ? 1 : (matches[5].str() == "-") ? -1 : std::stoi(matches[5].str());
            c = std::stoi(matches[6].str());
        }

        if (a == 0) {
            std::cout << "No solution (coefficient of x is 0)." << std::endl;
        } else {
            double x = (c - b) / static_cast<double>(a); // Correct calculation for x
            std::cout << "x = " << x << std::endl;
        }
    } else {
        std::cout << "Invalid equation format." << std::endl;
    }

    return 0;
}