#include <point.h>
#include <maze.h>

using std::min;
using std::max;

namespace ecn
{

Maze Point::maze;

// final print
// maze deals with the color, just tell the points
void Point::print(const Point &parent) const
{
        int x_incr(0), y_incr(0);

        if(x - parent.x)
            x_incr = x - parent.x > 0 ? 1 : -1;
        else
            y_incr = y - parent.y > 0 ? 1 : -1;
        int k = 1;
        while(parent.x + k*x_incr != x || parent.y + k*y_incr != y)
        {
            maze.passThrough(parent.x + k*x_incr,
                             parent.y + k*y_incr);
            k++;
        }

    maze.passThrough(x, y);
}

void Point::start()
{
    maze.write(x, y);
}

// online print, color depends on closed / open set
void Point::show(bool closed, const Point & parent)
{
    const int b = closed?255:0, r = closed?0:255;
    if(x != parent.x)
        for(int i = min(x, parent.x); i <= max(x, parent.x);++i)
            maze.write(i, y, r, 0, b, false);
    else
        for(int j = min(y, parent.y); j <= max(y, parent.y);++j)
            maze.write(x, j, r, 0, b, false);
    maze.write(x, y, r, 0, b);
}


}
