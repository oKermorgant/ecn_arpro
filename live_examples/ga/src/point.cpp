#include <algorithm>
#include <point.h>
#include <random>

double rand(double min, double max)
{
  static std::mt19937 generator;
  static std::uniform_real_distribution<double> rand01(0, 1);

  return min + (max-min)*rand01(generator);
}






void Point::computeCost()
{
  cost = 20 + x*x + y*y - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
}


void Point::randomize()
{
  x = rand(-5, 5);
  y = rand(-5, 5);
  computeCost();
}


void Point::crossFrom(const Point &p1, const Point &p2)
{

  const auto alpha{rand(0, 1)};
  x = alpha*p1.x + (1-alpha)*p2.x;
  y = alpha*p1.y + (1-alpha)*p2.y;
  computeCost();
}

void Point::mutate()
{
  // do stuff
  x += rand(-0.1, 0.1);
  y += rand(-0.1, 0.1);

  x = std::clamp(x, -5., 5.);
  y = std::clamp<double>(y, -5, 5);
  computeCost();
}

