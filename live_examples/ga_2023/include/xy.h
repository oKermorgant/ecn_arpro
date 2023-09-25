#ifndef XY_H
#define XY_H
#include <rand_range.h>
#include <iostream>
#include <algorithm>

class XY
{
  double cost;

  void computeCost()
  {
    const int A = 10;
    cost = 2 * A + (x * x - A * std::cos(2 * M_PI * x)) + (y * y - A * std::cos(2 * M_PI * y));
  }
public:

  double x = 0, y = 0;

  void randomize()
  {
    this->x = randRange(-5.,5.);
    this->y = randRange(-5.,5.);
    this->computeCost();
  }

  auto getCost() const
  {
    return cost;
  }


  XY crossAndMutate(const XY &other) const
  {
    const auto alpha = randRange(0.,1.);
    XY child;
    child.x = alpha*x + (1-alpha)*other.x;
    child.y = alpha*y + (1-alpha)*other.y;
    //child.computeCost();

    child.mutate();

    return child;
  }

  void mutate()
  {
    y += randRange(-.5, .5);

    x = std::clamp(x + randRange(-.5, .5), -5., 5.);
    y = std::clamp<double>(y, -5, 5);

    computeCost();
  }

  void print() const
  {
    std::cout << "(" << x << ", " << y << ") -> " << cost << '\n';
  }

};


#endif // XY_H
