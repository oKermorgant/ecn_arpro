#pragma once

#include <iostream>
class Point
{
  double x, y;
  double cost;

  void computeCost();

public:

  void randomize();
  double getCost() const {return cost;}
  void crossFrom(const Point &p1, const Point &p2);

  void print() const {std::cout << cost << " @ (" << x << ", " << y << ")\n";}

  void mutate();





};
