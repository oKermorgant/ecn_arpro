#include <algorithm>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;


struct Point
{
  Point(double _x, double _y) : x(_x), y(_y) {}

  double angle(const Point &other) const
  {
    return atan2(other.y-y, other.x-x);
  }

  double dist_square(const Point &other) const
  {
    const double dx(other.x-x);
    const double dy(other.y-y);
    return dx*dx + dy*dy;
  }

  double dist(const Point &other) const
  {
    return sqrt(dist_square(other));
  }

  // how to display a point with <<
  friend std::ostream& operator<<(std::ostream &oss, const Point &P)
  {
    oss << "(" << P.x << ", " << P.y << ")";
    return oss;
  }

protected:
  double x, y;
};

void printAll(const std::vector<Point> &points)
{
  for(size_t i = 0; i < points.size(); ++i)
  {
    if(i != 0)
      std::cout << " -> ";
    std::cout << points[i];
  }
  std::cout << std::endl << std::endl;
}

int main()
{
  std::vector<Point> points;
  points.emplace_back(0,0);
  points.emplace_back(1,1);
  points.emplace_back(0,1);
  points.emplace_back(1,0);

  std::cout << "As initially defined\n";
  printAll(points);

  const Point Pd(0.1, 0.5);
  std::cout << "Sorting according to (squared) distance to " << Pd << std::endl;
  std::sort(points.begin(), points.end(), [Pd](const auto &P1, const auto &P2)
  {
    return Pd.dist_square(P1) < Pd.dist_square(P2);
  });
  printAll(points);

  const auto &P0(points.front());
  std::cout << "Sorting according to angle from " << P0 << std::endl;
  std::sort(points.begin()+1, points.end(), [P0](const auto &P1, const auto &P2)
  {
    return P0.angle(P1) < P0.angle(P2);
  });
  printAll(points);
}
