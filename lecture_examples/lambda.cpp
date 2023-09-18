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

  void print() const
  {
    std::cout << *this << " ";
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
  for(auto &p: points)
    std::cout << p << " ";
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


  const Point Pc(2, 0.4);
  std::cout << "Sorting according to (squared) distance to " << Pc << std::endl;
  std::sort(contour.begin(), contour.end(), [Pc](const auto &P1, const auto &P2)
  {
    return Pc.dist_square(P1) < Pc.dist_square(P2);
  });

  printAll(contour);


  std::cout << "Sorting according to angle from " << Pc << std::endl;
  std::sort(contour.begin(), contour.end(), [Pc](const auto &P1, const auto &P2)
  {
    return Pc.angle(P1) < Pc.angle(P2);
  });
  printAll(contour);

  const auto first_far = std::partition(contour.begin(), contour.end(), [](const auto &P)
  {
    return P.norm() < 1.2;
  });
  printAll(contour);



  std::cout << "Points close to 0: ";
  std::for_each(contour.begin(), first_far, [](const auto &P){P.print();});
  std::cout << std::endl;
  std::cout << "Points far from 0: ";
  std::for_each(first_far, contour.end(), [](const auto &P){P.print();});
  std::cout << std::endl;

  if(first_far != contour.end())
  {
    // display first far point
    const auto index = std::distance(contour.begin(), first_far);
    std::cout << "Point #" << index << " / norm = " <<first_far->norm() << " >= 1.2" << std::endl;
  }



  int count = 0;
  for(int i = 0; i < contour.size(); ++i)
  {
    if(contour[i].norm() < 1.2)
      count += 1;
  }
  count++;







}
