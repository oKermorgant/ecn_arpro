#ifndef XY_H
#define XY_H

#include <iostream>
#include <rand_utils.h>

class XY
{

  double x_{10}, y_{10}, cost_{10};
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

  }

  bool operator<(XY other)
  {
    return cost_ < other.cost_;
  }

  XY cross(XY other)
  {

    return XY();
  }

  void mutate()
  {

  }
};


#endif // XY_H
