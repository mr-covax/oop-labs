#include <cmath>

#include "base/polygon.h"

double Polygon::realArea()
{
    double result = 0;
    for (int i{}; i < pointCount; ++i)
    {
        int n = (i + 1) % pointCount;
        result += (points[i].x * points[n].y);
        result -= (points[n].x * points[i].y);
    }
    return result / 2;
}

double Polygon::getArea()
{
    return std::abs(realArea());
}

Point Polygon::getCenter()
{
    double coefficient = 6 * realArea();

    Point result{};
    result.x = result.y = 0;

    for (int i{}; i < pointCount; ++i)
    {
        int n = (i + 1) % pointCount;
        double common = (points[i].x * points[n].y) - (points[n].x * points[i].y);

        result.x += (points[i].x + points[n].x) * common;
        result.y += (points[i].y + points[n].y) * common;
    }

    result.x /= coefficient;
    result.y /= coefficient;
    return result;
}

bool Polygon::compare(const Polygon &other) const
{
    if (pointCount != other.pointCount)
    {
        return false;
    }

    for (int i{}, j{}; j < pointCount; ++j)
    {
        if (i == pointCount)
        {
            return true;
        }
        else if (points[i] == other.points[j])
        {
            ++i;
            j = -1;
        }
    }
    return false;
}