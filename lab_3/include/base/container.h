#include <initializer_list>

#include "base/figure.h"

class FigureContainer
{
    private:
        static const int allocatedSize = 32;
        Figure* shapeArray[allocatedSize]{nullptr};
        int top = 0;

    public:
        FigureContainer() = default;
        FigureContainer(std::initializer_list<Figure*> shapes);
        
        Figure* at(const int index);
        int append(Figure* figPtr);
        void remove(const int index);

        ~FigureContainer() = default;
};