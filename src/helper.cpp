#include "headers/helper.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

// Function to format number
std::string FormatNumber(int number) {
    std::ostringstream oss;
    if (number >= 1000000) {
        oss << std::fixed << std::setprecision(1) << (number / 1000000.0) << "M";
    } else if (number >= 1000) {
        oss << std::fixed << std::setprecision(1) << (number / 1000.0) << "K";
    } else {
        oss << number;
    }
    return oss.str();
}