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

    // prints the grid with all positions from parent
    virtual void print(const Point &parent) const;

    void start();

    virtual void show(bool closed, const Point &parent);

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

    double h(const Point &goal, bool use_manhattan) const
    {
        if(use_manhattan)
            return  abs(x-goal.x) + abs(y-goal.y);
        return 1.5*sqrt((x-goal.x)*(x-goal.x) + (y-goal.y)*(y-goal.y));
    }

    int x, y;
    static Maze maze;
};


}

#endif // POINT_H
