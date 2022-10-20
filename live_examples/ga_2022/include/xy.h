#ifndef XY_H
#define XY_H

#include <rand_range.h>
#include <iostream>

class XY
{
  double x{}, y{}, cost{};

  XY(double x, double y) : x{x}, y{y}
  {
  }

  void computeCost()
  {
    cost = 20 + x*x + pow(y, 2) - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
    if(std::abs(x) < 1e-6 || std::abs(y) < 1e-6)
      throw std::runtime_error("wierd x y");

  }

public:

  XY()
  {
    randomize();
  }

  auto getCost() {return cost;}

  void randomize()
  {
    x = randRange(-5., 5.);
    y = randRange(-5., 5.);
    computeCost();
  }

  void print() const
  {
    std::cout << "(" << x << ", " << y << ") @ " << cost << std::endl;
  }

  XY crossAndMutate(XY other)
  {
    const auto alpha{randRange(0., 1.)};
    XY crossing(alpha * x + (1-alpha)*other.x,
                alpha*y + (1-alpha)*other.y);

    // mutate
    crossing.x += randRange(-0.5, 0.5);
    crossing.y += randRange(-0.5, 0.5);

    crossing.computeCost();
    return crossing;
  }

  bool operator<(XY other) const
  {
    return cost < other.cost;
  }
};




#endif // XY_H
