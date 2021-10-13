#include <random>
#include <iostream>

#include "rastrigin.h"
#include "genetic_algo.h"


void XY::randomize()
{
  // TODO random coord between -5 and 5
  x = rand(-5, 5);
  y = rand(-5, 5);

  computeCost();
}

XY XY::cross(XY other) const
{
  XY crossing;

  const auto t{rand(0.05,0.95)};
  crossing.x = x + t*(other.x-x);
  crossing.y = y + t*(other.y-y);

  return crossing;
}

void XY::mutate()
{
  x += 0.5*rand(-1,1);
  y += 0.5*rand(-1,1);
  sat(x);
  sat(y);

  computeCost();
}

void XY::computeCost()
{
  cost = 20 + x*x + y*y - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
}

double XY::rand(double min, double max)
{
  return min + (max-min)*rand01(engine);
}

void XY::print() const
{
  std::cout << "(" << x << ", " << y << ") : "
            << cost << std::endl;
}

void XY::sat(double &coord)
{
  if(coord < -5)
    coord = -5;
  else if(coord > 5)
    coord = 5;
}

std::default_random_engine XY::engine;
std::uniform_real_distribution<> XY::rand01;


int main()
{

  auto best{geneticAlgo<XY>()};

  best.print();
}
