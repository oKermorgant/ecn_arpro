#ifndef XY_H
#define XY_H
#include <random>
#include <iostream>
#include <algorithm>

class XY
{
  static inline std::default_random_engine engine;
  static inline std::uniform_real_distribution<double> range{-5, 5};
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
    this->x = range(engine);
    this->y = range(engine);
    this->computeCost();
  }

  bool operator<(const XY &other) const
  {
    return this->cost < other.cost;
  }

  XY crossAndMutate(const XY &other) const
  {
    static std::uniform_real_distribution<double> alpha_range(0,1);

    const auto alpha = alpha_range(engine);
    XY child;
    child.x = alpha*x + (1-alpha)*other.x;
    child.y = alpha*y + (1-alpha)*other.y;
    //child.computeCost();

    child.mutate();

    return child;
  }

  void mutate()
  {
    static std::uniform_real_distribution<double> mutation(-0.5, 0.5);

    y += mutation(engine);

    x = std::clamp(x + mutation(engine), -5., 5.);
    y = std::clamp<double>(y, -5, 5);

    computeCost();
  }

  void print() const
  {
    std::cout << "(" << x << ", " << y << ")\n";
  }

};


#endif // XY_H
