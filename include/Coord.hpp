//
// Created by qingzhixing on 2025/6/3.
//

#ifndef COORD_H
#define COORD_H


class Coord
{
public:
    int x;
    int y;
    Coord(const int x, const int y) : x(x), y(y) {}

public:
    Coord operator+(const Coord& other) const { return {x + other.x, y + other.y}; }
    Coord operator-(const Coord& other) const { return {x - other.x, y - other.y}; }
    bool operator==(const Coord& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Coord& other) const { return x != other.x || y != other.y; }
    Coord& operator+=(const Coord& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Coord& operator-=(const Coord& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};


#endif // COORD_H
