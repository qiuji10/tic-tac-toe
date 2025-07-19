#pragma once
#include <iostream>

void setColor(int textColorCode) {
    std::cout << "\033[" << textColorCode << "m";
}