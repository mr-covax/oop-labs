#pragma once

#include <iostream>
#include <initializer_list>

#include "base/polygon.h"

class Hexagon : public Polygon
{
    public:
        Hexagon();
        Hexagon(std::initializer_list<Point> vertices);

        operator double();

        bool operator==(const Hexagon &other) const;
        Hexagon &operator=(const Hexagon &other);
        Hexagon &operator=(Hexagon &&other);

        friend std::istream &operator>>(std::istream &is, Hexagon &tr);
        friend std::ostream &operator<<(std::ostream &os, const Hexagon &tr);

        ~Hexagon() override;
};