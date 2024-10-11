#include "shapes/triangle.h"

#include <algorithm>

Triangle::Triangle()
{
    pointCount = 3;
    points = new Point[pointCount];
}

Triangle::Triangle(std::initializer_list<Point> vertices): Triangle{}
{
    if (vertices.size() != pointCount) {
        throw std::invalid_argument("Invalid vertex count.");
    }
    std::copy(vertices.begin(), vertices.end(), points);
}

Triangle::operator double()
{
    return Polygon::getArea();
}

Triangle &Triangle::operator=(const Triangle &other)
{
    for (int i{}; i < pointCount; ++i)
    {
        points[i] = other.points[i];
    }
    return *this;
}

Triangle &Triangle::operator=(Triangle &&other)
{
    if (points != nullptr)
    {
        delete[] points;
    }
    points = other.points;
    other.points = nullptr;
    return *this;
}

bool Triangle::operator==(const Triangle &other) const
{
    return Polygon::compare(other);
}

std::istream &operator>>(std::istream &is, Triangle &tr)
{
    for (int i{}; i < tr.pointCount; ++i)
    {
        is >> tr.points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Triangle &tr)
{
    os << "Triangle( ";
    for (int i{}; i < tr.pointCount; ++i)
    {
        os << tr.points[i] << ' ';
    }
    return os << ')';
}

Triangle::~Triangle()
{
    if (points != nullptr)
    {
        delete[] points;
    }
}