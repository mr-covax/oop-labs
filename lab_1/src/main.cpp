#include <iostream>
#include "divider.h"

int main() {
    std::cout << "Enter the width and heigth of the bar in squares\n";

    int width, heigth;

    std::cout << "Width: ";
    std::cin >> width;
    std::cout << "Heigth: ";
    std::cin >> heigth;

    int cuts = get_min_divs(width, heigth);
    if (cuts != 0)
        std::cout << "You need " << cuts << " cuts" << std::endl;
    else
        std::cout << "The dimensions of your bar are invalid." << std::endl;

    return 0;
}
