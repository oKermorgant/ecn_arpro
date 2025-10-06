#ifndef XY_H
#define XY_H

#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>

double rand01()
{
  static std::default_random_engine engine;
  static std::uniform_real_distribution<double> unif(0,1);
  return unif(engine);
}

template <class T> T rand(T min, T max)
{
  return min + rand01()*(max-min);
}

class XY
{
private:
  double cost_{100}, x_, y_;

void computeCost()
  {
    cost_ =  x_+x_ + y_*x_ - 10*(cos(2*M_PI*x_) + cos(2*M_PI*y_));
  }

public:

  auto x() const {return x_;}
  auto y() const {return y_;}
  auto cost() const {return cost_;}


  void print() const
  {
    std::cout << '(' << x() << "," << y() << ") -> " << cost() << std::endl;
  }

  void randomize()
  {
    x_ = rand(-5., 5.);
    y_ = rand<double>(-5, 5);
    computeCost();
  }


  bool operator<(const XY& other)  const
  {
    return cost_ < other.cost_;
  }

  XY cross(const XY &other) const
  {
    const auto alpha{rand01()};
    XY out;
    out.x_ = alpha*x_ + (1-alpha)*other.x();
    out.y_ = alpha*y_ + (1-alpha)*other.y();
    out.computeCost();
    return out;
  }

  void mutate()
  {
    x_ = std::clamp<double>(x_ + rand(-.5, .5), -5, 5);
    y_ = std::clamp(y_ + rand(-.5, .5), -5., 5.);
    computeCost();
  }


};

#endif // XY_H
