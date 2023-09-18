#ifndef XY_H
#define XY_H

#include <rand_range.h>
#include <individual.h>
#include <iostream>

class XY : public Individual
{
  double x{}, y{};

  XY(double x, double y) : x{x}, y{y}
  {
  }

  void computeCost()
  {
    cost = 20 + x*x + pow(y, 2) - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
    //if(std::abs(x) < 1e-6 || std::abs(y) < 1e-6)
      //throw std::runtime_error("wierd x y");
  }

public:

  XY()
  {
    randomize();
  }

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
    XY crossing;
    crossing.crossAndMutate(*this, other);
    return crossing;
  }

  void crossAndMutate(XY p1, XY p2)
  {
    const auto alpha{randRange(0., 1.)};
    x = alpha * p1.x + (1-alpha)*p2.x;
    y = alpha * p1.y + (1-alpha)*p2.y;

    // mutate
    x += randRange(-0.5, 0.5);
    y += randRange(-0.5, 0.5);

    computeCost();
  }

};




#endif // XY_H
