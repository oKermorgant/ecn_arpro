#include <iostream>
#include <vector>
#include <algorithm>

#include "robot.h"

using Fleet = std::vector<Robot>;

void print(const Fleet& fleet)
{
  std::cout << "Fleet is: \n";
  for(auto &robot: fleet)
    std::cout << " - " << robot << "\n";
  std::cout << std::endl;
}

auto nearestTo(const Fleet &fleet, double x, double y)
{
  return std::min_element(fleet.begin(), fleet.end(),

  [x,y](const auto &r1, const auto &r2)
  {
    return r1.distance(x, y) < r2.distance(x,y);
  });


}



int main()
{
  Fleet fleet(10);

  print(fleet);

  // how many robots with negative coord?
  std::cout << std::count_if(fleet.begin(), fleet.end(), [](const auto &robot)
  {return robot.x < 0;})
            << " with negative x-coord" << std::endl;

  std::cout << "Closest to (1,1) is "
            << *nearestTo(fleet, 1, 1) << std::endl;


  // sort robots according to their distance to (0,0)
  std::sort(fleet.begin(), fleet.end(), [](const auto &r1, const auto &r2)
  {
    return r1.distance(0,0) < r2.distance(0,0);
  });
  print(fleet);


  // sort robots according to the y-coord
  std::sort(fleet.begin(), fleet.end(), [](const auto &r1, const auto &r2)
  {
    return r1.y < r2.y;
  });
  print(fleet);


  // any robot has x = 0.3?
  auto where{std::find_if(fleet.begin(), fleet.end(), [](const auto &robot)
    {
      return robot.x == 0.3;
    })};


  if(where != fleet.end())
    std::cout << *where
              << " (index = " << std::distance(fleet.begin(), where) << ')'
              << std::endl;
  else
    std::cout << "No robot has x = 0.3\n";
}
