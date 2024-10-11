#include <algorithm>
#include <stdexcept>

#include "shapes/hexagon.h"

Hexagon::Hexagon()
{
    pointCount = 6;
    points = new Point[pointCount];
}

Hexagon::Hexagon(std::initializer_list<Point> vertices): Hexagon{}
{
    if (vertices.size() != pointCount) {
        throw std::invalid_argument("Invalid vertex count.");
    }
    std::copy(vertices.begin(), vertices.end(), points);
}

Hexagon::operator double()
{
    return Polygon::getArea();
}

Hexagon &Hexagon::operator=(const Hexagon &other)
{
    for (int i{}; i < pointCount; ++i)
    {
        points[i] = other.points[i];
    }
    return *this;
}

Hexagon &Hexagon::operator=(Hexagon &&other)
{
    if (points != nullptr)
    {
        delete[] points;
    }
    points = other.points;
    other.points = nullptr;
    return *this;
}

bool Hexagon::operator==(const Hexagon &other) const
{
    return Polygon::compare(other);
}

std::istream &operator>>(std::istream &is, Hexagon &tr)
{
    for (int i{}; i < tr.pointCount; ++i)
    {
        is >> tr.points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Hexagon &tr)
{
    os << "Hexagon( ";
    for (int i{}; i < tr.pointCount; ++i)
    {
        os << tr.points[i] << ' ';
    }
    return os << ')';
}

Hexagon::~Hexagon()
{
    if (points != nullptr)
    {
        delete[] points;
    }
}