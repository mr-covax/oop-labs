#include <iostream>

struct Point
{
    double x, y;

    bool operator==(const Point &other) const
    {
        return (x == other.x) && (y == other.y);
    }

    friend std::istream &operator>>(std::istream &is, Point &p)
    {
        return is >> p.x >> p.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        return os << '{' << p.x << "," << p.y << '}';
    }
};