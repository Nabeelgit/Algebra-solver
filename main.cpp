#include <iostream>
#include <string>
#include <regex>
#include <cmath>

// Function to calculate logarithm with a specified base
double log_base(double base, double number) {
    return std::log(number) / std::log(base);
}

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
    std::cout << "Enter an equation (e.g., 2x+log(10,2)=12): ";
    std::getline(std::cin, equation);

    // Remove all spaces from the input equation
    equation = remove_spaces(equation);

    // Regex to find log(base, number) and replace it with its computed value
    std::regex log_expr("log\\((\\d+),(\\d+)\\)");
    std::smatch log_matches;
    while (std::regex_search(equation, log_matches, log_expr)) {
        double base = std::stod(log_matches[1].str());
        double number = std::stod(log_matches[2].str());
        double log_value = log_base(base, number);
        equation.replace(log_matches.position(0), log_matches.length(0), std::to_string(log_value));
    }

    // Regex to parse the linear equation
    std::smatch matches;
    std::regex expr("([+-]?\\d*)x([+-]?\\d*)=([+-]?\\d*)");

    if (std::regex_search(equation, matches, expr)) {
        int a = (matches[1].str().empty() || matches[1].str() == "+") ? 1 : (matches[1].str() == "-") ? -1 : std::stoi(matches[1].str());
        int b = matches[2].str().empty() ? 0 : std::stoi(matches[2].str());
        int c = std::stoi(matches[3].str());

        if (a == 0) {
            std::cout << "No solution (coefficient of x is 0)." << std::endl;
        } else {
            double x = (c - b) / static_cast<double>(a);
            std::cout << "x = " << x << std::endl;
        }
    } else {
        std::cout << "Invalid equation format." << std::endl;
    }

    return 0;
}