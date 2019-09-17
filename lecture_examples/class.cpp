#include <iostream>

struct MyRobot
{
private:
  double x_ = 0;

public:
  MyRobot() {}

  MyRobot(double _x)
  {
    x_ = _x;
    double x;
  }

  double x()
  {
    std::cout << x_ << std::endl;
    return x_;
  }
};

int main()
{
  MyRobot rob(1);


  rob.x();
}
