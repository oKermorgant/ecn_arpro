#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Robot
{
  double x_ = 0, y_, theta;
  string name;
  Robot(string name)
  {
    this->name = name;
  }

  double x()
  {
    std::cout << x_ << std::endl;
    return x_;
  }

  double distanceTo(Robot other)
  {
    return 0;
  }
};

class Matrix
{

  int rows, columns;
  vector<double> data;

public:
  Matrix(int rows, int columns,double val = 0)
  {
    data.resize(rows*columns, val);
    this->rows = rows;
    this->columns = columns;
  }

  void resize(int rows, int columns)
  {

  }

  double at(int row, int col)
  {
    return 0;
  }
};





int main()
{
  Robot rob("R2D2");

  int i = 0;
  float v;
  if(i == v) {}


  rob.x();

  Matrix M(4, 3);




}
