#include <iostream>

#include "base/figure.h"
#include "base/container.h"

#include "shapes/octagon.h"
#include "shapes/hexagon.h"
#include "shapes/triangle.h"

int main() {
    Triangle tr1;
    Triangle tr2 = { {0, 0}, {3, 0}, {0, 3} };

    Hexagon hx1;
    Hexagon hx2 = {
        {2.95, 0}, {1.39, 2.73}, {-1.57, 2.72}, 
        {-3.01, 0.12}, {-1.48, -2.59}, {1.53, -2.74} 
    };
    
    Octagon oc1;
    Octagon oc2 = { 
        {2.50, 0.00}, {1.50, 2.50}, {-1.00, 2.83}, {-2.50, 1.50}, 
        {-2.83, -1.00}, {-1.50, -2.50}, {1.00, -2.83}, {2.00, -1.50}
    };

    std::cin >> tr1 >> hx1 >> oc1;
    
    FigureContainer container{&tr1, &hx1, &oc1, &tr2, &hx2, &oc2}; 

    //
    // Part 1: print all the names
    // 
    std::cout << "\n=== print names ===" << std::endl;

    std::cout << tr1 << '\n'
        << tr2 << '\n'
        << hx1 << '\n'
        << hx2 << '\n'
        << oc1 << '\n'
        << oc2 << std::endl;

    //
    // Part 2: print the area and the center of every shape
    // in the container.
    //
    std::cout << "\n=== getArea() ===" << std::endl;

    for (int i{}; i < 6; ++i)
        std::cout << container.at(i)->getArea() << std::endl;

    //
    // Part 3: print the centers of every shape inside
    // the container
    //
    std::cout << "\n=== getCenter() ===" << std::endl;

    for (int i{}; i < 6; ++i)
        std::cout << container.at(i)->getCenter() << std::endl;

    // 
    // Part 4: calculate the total area of all the shapes
    // 
    std::cout << "\n=== globalArea ===" << std::endl;
    
    double globalArea = 0;
    for (int i{}; i < 6; ++i)
        globalArea += container.at(i)->getArea();
    
    std::cout << globalArea << std::endl;

    //
    // Part 5: destroy several elements from the
    // container
    //
    std::cout << "\n=== removal test ===" << std::endl;

    container.remove(0);
    container.remove(0);
    for (int i{}; i < 4; ++i)
        std::cout << container.at(i)->getCenter() << std::endl;

    return 0;
}

