#include "robot.h"

double Robot::distance(double x, double y) const
{
  const auto dx{x-this->x};
  const auto dy{y-this->y};
  return sqrt(dx*dx + dy*dy);
}

