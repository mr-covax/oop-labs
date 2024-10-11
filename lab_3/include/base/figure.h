#pragma once

#include "base/point.h"

class Figure
{
    protected:
        Figure() = default;

    public:
        virtual double getArea() = 0;
        virtual Point getCenter() = 0;
        virtual ~Figure() = default;
};