#ifndef XY_H
#define XY_H

#include <rand_range.h>
#include <iostream>
#include <algorithm>

struct XY
{
private:
  double x{}, y{}, cost{};

public:
    auto randomize()
    {
      x = randRange(-5.,5.);
      y = randRange(-5.,5.);
      computeCost();
    }

    void print() const
    {
      std::cout << "(" << x << ", " << y << ") -> " << cost << '\n';
    }

    auto getCost() const {return cost;}
    auto getX() const {return x;}
    auto getY() const {return y;}


    XY cross(XY xy2)
    {
      XY crossed;

      const auto alpha{randRange(0.,1.)};
      crossed.x = alpha*x + (1-alpha)*xy2.x;
      crossed.y = alpha*y + (1-alpha)*xy2.y;

      crossed.computeCost();

      return crossed;
    }

    void mutate()
    {

      const auto dx{randRange(-0.5, .5)};
      const auto dy{randRange(-0.5, .5)};

      x = std::clamp<double>(x + dx, -5, 5);
      y = std::clamp(y + dy, -5., 5.);

      computeCost();
    }

    bool operator<(XY other) const
    {
      return cost < other.cost;
    }


void computeCost()
{
  cost = 20 + pow(x,2) + pow(y,2)
      - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
}

};

#endif // XY_H
