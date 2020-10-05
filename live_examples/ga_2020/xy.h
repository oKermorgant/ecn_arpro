#ifndef XY_H
#define XY_H

#include <random>
#include <iostream>

std::mt19937 device;
std::uniform_real_distribution<double> unitRand(0,1);

class XY
{
private:
  double x = 0, y = 0;
  double cost;


  void computeCost()
  {
    cost = 20 + x*x + y*y
        - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
  }

public:
  static int created;
  XY() {created++;}

  void print()
  {
    std::cout << cost << " at (" << x << ", " << y << ")"
              << std::endl;

  }

  double eval() const
  {
    return cost;
  }

  void randomize()
  {
    x = -5 + 10*unitRand(device);
    y = -5 + 10*unitRand(device);
    computeCost();
  }

  void cross(const XY &p1, const XY &p2)
  {
    const double alpha(unitRand(device));

    x = alpha*p1.x + (1-alpha)*p2.x;
    y = alpha*p1.y + (1-alpha)*p2.y;
  }

  XY cross(XY other)
  {
    XY generated;

    return generated;
  }

  void mutate()
  {
    const double modif(0.1);

    x += -modif + 2*modif*unitRand(device);
    y += -modif + 2*modif*unitRand(device);

    x = std::min(5., std::max(-5., x));
    y = std::min(5., std::max(-5., y));

    computeCost();
  }
};
int XY::created = 0;


#endif
