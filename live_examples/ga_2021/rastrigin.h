#ifndef RASTRIGIN_H
#define RASTRIGIN_H

#include <random>

class XY
{
public:
  void randomize();

  void cross(const XY &p1, const XY &p2);

  void mutate();

  void computeCost();

  double cost;

  static double rand(double min, double max);

  void print() const;

private:

  double x=100, y=100;

  static std::default_random_engine engine;
  static std::uniform_real_distribution<> rand01;

  static void sat(double &coord);
};

#endif // RASTRIGIN_H
