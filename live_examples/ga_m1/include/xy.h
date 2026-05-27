#ifndef XY_H
#define XY_H

#include <iostream>
#include <rand_utils.h>
#include <algorithm>

class XY
{

  double x_{10}, y_{10}, cost_{10};

  void updateFrom(double x, double y)
  {
    x_ = x;
    y_ = y;
    cost_ = 20 + (x_*x_ - 10 * cos(2 * M_PI * x_)) + (y_*y_ - 10 * cos(2 * M_PI * y_));
  }

public:

  // getters
  auto x() {return x_;}
  auto y() {return y_;}
  auto cost() {return cost_;}

  void print()
  {
    std::cout << '(' << x() << ", " << y()
    << ") @ " << cost() << std::endl;
  }

  void randomize()
  {
    updateFrom(rand_double(-5, 5),
               rand_double(-5, 5));
  }

  bool operator<(XY other) const
  {
    return cost_ < other.cost_;
  }

  XY crossAndMutate(XY other)
  {
    const auto alpha{rand_double(0, 1)};
    XY out;
    out.x_ = alpha*x_ + (1-alpha)*other.x_;
    out.y_ = alpha*y_ + (1-alpha)*other.y_;
    out.mutate();
    return out;
  }

  void mutate()
  {
    updateFrom(std::clamp(x_ + rand_double(-.1, .1), -5., 5.),
               std::clamp<double>(y_ + rand_double(-.1, .1), -5, 5));
  }
};


#endif // XY_H
