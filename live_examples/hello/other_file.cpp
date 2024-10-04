//please compile

#include <iostream>
#include <vector>
#include <algorithm>

class Point
{
public:
  int x;
  int y;
  std::string name;
  auto operator==(Point other) const
  {
    return x == other.x && y == other.y;
  }
};

auto print(const Point &p)
{
  std::cout << "(" << p.x << ", " << p.y << ")\n";
}

auto print(const std::vector<Point> &c)
{
  for(auto &p: c)
  {
    print(p);
  }
}

int main ()
{

  std::vector<Point> contour;

  contour.push_back({1,2, "p1"});
  contour.push_back({3,4, "p2"});
  contour.push_back({0,4, "p2"});
  contour.push_back({-1,4, "p2"});


  print(contour);

  std::vector x{1,2,3};



  std::sort(contour.begin(), contour.end(), [](auto &p1, auto &p2)
  {
    return p1.x < p2.x;
  });

  std::cout << std::count_if(contour.begin(), contour.end(), [](auto &p)
  {
    return p.x < 0;
  }) << std::endl;

//print(contour);



}
