#pragma once

#include <iostream>
#include <initializer_list>

#include "base/polygon.h"

class Octagon : public Polygon
{
    public:
        Octagon();
        Octagon(std::initializer_list<Point> vertices);

        operator double();

        bool operator==(const Octagon &other) const;
        Octagon &operator=(const Octagon &other);
        Octagon &operator=(Octagon &&other);

        friend std::istream &operator>>(std::istream &is, Octagon &tr);
        friend std::ostream &operator<<(std::ostream &os, const Octagon &tr);

        ~Octagon() override;
};