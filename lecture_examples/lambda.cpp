#include <algorithm>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;


struct Point
{
  Point(double _x=0, double _y=0) : x(_x), y(_y) {}

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

  double norm() const {return dist({0,0});}

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

  static bool compareNorms(const Point &p1, const Point &p2)
  {
    return p1.norm() < p2.norm();
  }
  
protected:
  double x, y;
};

void printAll(const std::vector<Point> &points)
{
  for(size_t i = 0; i < points.size(); ++i)
  {
    if(i != 0)
      std::cout << " ";
    std::cout << points[i];
  }
  std::cout << std::endl << std::endl;
}

int main()
{
  std::vector<Point> contour;

  contour.emplace_back(0,0);
  contour.emplace_back(1,1);
  contour.emplace_back(2,0);
  contour.emplace_back(0,1);

  
  std::cout << "As initially defined\n";
  printAll(contour);
  
  
  std::cout << "Sorting according to norm" << std::endl;
  std::sort(contour.begin(), contour.end(), Point::compareNorms);
  printAll(contour);


  const Point Pd(2, 0.4);
  std::cout << "Sorting according to (squared) distance to " << Pd << std::endl;
  std::sort(contour.begin(), contour.end(), [Pd](const auto &P1, const auto &P2)
  {
    return Pd.dist_square(P1) < Pd.dist_square(P2);
  });

  printAll(contour);


  std::cout << "Sorting according to angle from " << Pd << std::endl;
  std::sort(contour.begin()+1, contour.end(), [Pd](const auto &P1, const auto &P2)
  {
    return Pd.angle(P1) < Pd.angle(P2);
  });
  printAll(contour);


 cout << std::count_if(contour.begin(), contour.end(), [](const auto &P)
  {
    return P.norm() < 1.2;
  }) << endl;

 int count = 0;
 for(int i = 0; i < contour.size(); ++i)
 {
   if(contour[i].norm() < 1.2)
      count += 1;
 }





}
