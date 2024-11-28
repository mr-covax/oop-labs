#include <iostream>
#include <string>
#include <logging/display.h>

void DisplayLogger::writeNum(size_t message) {
    std::cout << message;
}

void DisplayLogger::writeStr(std::string message) {
    std::cout << message;
}