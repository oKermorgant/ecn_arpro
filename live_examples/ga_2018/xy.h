#ifndef XY_H
#define XY_H
#include <iostream>

class XY
{
 private:
    double x, y;

public:
    double cost;
    XY(int min = -5, double max = 5);
    void computeCost();

    friend bool operator<(const XY& o1, const XY& o2)
    {
        return o1.cost < o2.cost;
    }

    void reset(const XY& p1, const XY& p2);

    void mutate();

    void print()
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

#endif // XY_H
