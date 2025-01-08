#ifndef POINT_H
#define POINT_H

#include <cstdlib>
#include <iostream>
#include <math.h>

namespace ecn
{

class Maze;

class Point
{
public:

    Point(int _x=0, int _y=0): x(_x), y(_y) {}

    void operator=(const Point &p)
    {
        x = p.x;
        y = p.y;
    }

    // prints the grid with all positions from next
    virtual void print(const Point &next) const;

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }

    // 2 positions are equal if they have the same x and y
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    inline int h(const Point &goal) const
    {
      return  abs(x-goal.x) + abs(y-goal.y);
    }

    int x, y;
    static Maze maze;
};


}

#endif // POINT_H
