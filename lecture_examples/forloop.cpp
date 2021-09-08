#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Robot
{
  double x, y, theta;
  string name;

  void move() {}

  double distanceTo(Robot other) const
  {
    return 0;
  }
};


int main(int argc, char ** argv)
{
  std::vector<Robot> fleet(10);

  Robot target;

  for(auto &robot: fleet)
  {
    if(robot.distanceTo(target) < 1)
      robot.move();


    cout << robot.distanceTo(target) << endl;
  }

  map<string, int> grades;
  grades["Olivier"] = 1;
  grades["Isaac"] = 4;
  grades["Helen"] = 3;

  for(auto &[name, grade]: grades)
  {
    cout << name << " got  " << grade << endl;
  }

  vector<pair<int, double>> pairs;
  pairs.push_back({1,3.14});
  pairs.push_back({2,7.14});

  for(auto [first, second]: pairs)
  {

  }








}
