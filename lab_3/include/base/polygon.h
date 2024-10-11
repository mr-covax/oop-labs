#pragma once

#include "base/figure.h"

class Polygon : public Figure
{
    protected:
        Point *points;
        int pointCount;
        double realArea();
        bool compare(const Polygon &other) const;
    
    public:
        double getArea() override;
        Point getCenter() override;
};