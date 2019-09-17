#include "xy.h"
#include <random>

XY::XY()
{
  randomize();
}

void XY::randomize()
{
  x_ = rand_range(-10, 10);
  y_ = rand_range(-10, 10);
  computeCost();
}

void XY::mutate()
{
  x_ += rand_range(-0.5, 0.5);
  y_ += rand_range(-0.5, 0.5);
  computeCost();
}

void XY::cross(const XY &p1, const XY &p2)
{
  const double a = rand_range(0, 1);
  x_ = a*p1.x_ + (1-a)*p2.x_;
  y_ = a*p1.y_ + (1-a)*p2.y_;

  computeCost();

}

void XY::print() const
{

}


void XY::computeCost()
{
 cost_ =  20 + x_*x_ + y_*y_ - 10* (cos(2*M_PI*x_) + cos(2*M_PI*y_));
}


double XY::rand_range(double min, double max)
{
  return min + static_cast<double>(rand())/RAND_MAX * (max - min);
}



