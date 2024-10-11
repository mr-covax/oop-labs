#include "base/container.h"

FigureContainer::FigureContainer(std::initializer_list<Figure*> shapes) {
    int i{};
    for (Figure* ptr : shapes) {
        shapeArray[i] = ptr;
        ++i;
    }
}

Figure* FigureContainer::at(const int index) {
    return shapeArray[index];
}

int FigureContainer::append(Figure* figPtr) {
    if (top >= allocatedSize) {
        return -1;
    }
    shapeArray[top] = figPtr;
    return top++;
}

void FigureContainer::remove(const int index) {
    for (int i{index + 1}; i < top; ++i) {
        std::cout << "Moving element " << i << std::endl;
        shapeArray[i - 1] = shapeArray[i];
    }
    --top;
}