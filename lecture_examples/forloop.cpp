#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


struct Robot
{
  double x=0, y=0, theta_=0;
  string name;

  Robot(std::string name = "")
  {
    this->name = name;
    std::cout << "Creating a robot called " << name << std::endl;
  }

  auto set_theta(double theta)
  {


  }

  auto get_x()
  {
    return x;
  }

  void move() {}

  double distanceTo(Robot other) const
  {
    return 0;
  }
};


int main(int argc, char ** argv)
{

  Robot robot("R2D2");




  std::vector<Robot> fleet(10);

  for(const auto &robot: fleet)
  {
    std::cout << robot.x << std::endl;
  }



  // decomposition into public member variables
  for(auto &[x,y,theta,name]: fleet)
  {
    x = 1;
  }








/*
  Robot target;

  for(auto &robot: fleet)
  {
    if(robot.distanceTo(target) < 1)
      robot.move();


    cout << robot.distanceTo(target) << endl;
  }
*/
  map<string, int> grades;
  grades["Olivier"] = 1;
  grades["Isaac"] = 4;
  grades["Helen"] = 3;

  for(auto &elem: grades)
  {
    cout << elem.first << " got  " << elem.second << endl;
  }

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
