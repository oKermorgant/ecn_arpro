#include <iostream>
#include <vector>

class Robot
{
private:
  std::string name_;
  double x = 0;

public:
  Robot(std::string name)
  {
    name_ = name;
  }

  void move()
  {
    x = 1;
  }

  double getX() const
  {
    return x;
  }

  std::string name() const
  {
    return name_;
  }
};


int main() {

  int   x        (4);
  Robot my_robot("R2D2");

  my_robot.move();

  std::cout << "I am " << my_robot.name() << " @ " << my_robot.getX() << std::endl;




}
