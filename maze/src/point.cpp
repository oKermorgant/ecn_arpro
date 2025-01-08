#include <point.h>
#include <maze.h>

using std::min;
using std::max;

namespace ecn
{

Maze Point::maze;

// final print
// maze deals with the color, just tell the points
void Point::print(const Point &next) const
{
  int x_incr(0), y_incr(0);

  if(x - next.x)
    x_incr = x - next.x > 0 ? -1 : 1;
  else
    y_incr = y - next.y > 0 ? -1 : 1;

  auto xp{x}, yp{y};

  while(xp != next.x || yp != next.y)
  {
    maze.passThrough(xp, yp);
    xp += x_incr;
    yp += y_incr;
  }
  maze.passThrough(next.x, next.y);
}


}
