#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;


struct Robot
{
  double x_ = 0, y_{}, theta_{};
  std::string name;
  explicit Robot(const std::string& name) : name(name) {}

  void print() const
  {
    std::cout << name << " is at " << x_ << ", " << y_ << '\n';
  }

  double x()
  {
    std::cout << x_ << std::endl;
    return x_;
  }

  double distanceTo(const Robot& other) const
  {
    return 0;
  }

  void variables(int x)
  {
    x_ = x;

    int x2;
  }
};



class Matrix
{
private:
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
    this->rows = rows;
    this->columns = columns;
    data.resize(rows * columns);
  }

  std::tuple<int,int> dim()
  {
    return {rows, columns};
  }

 double at(int row, int col)
  {
    return 0;
  }
};





int main()
{
  Robot rob("R2D2"), target("C3PO");
  rob.print();

  std::vector<Robot> fleet;

  for(auto name: {"R2D2", "C3PO", "BB8"})
    fleet.emplace_back(name);

  for(const auto &r1: fleet)
  {
    for(const auto &r2: fleet)
    {
      std::cout << r1.name << " is at "
                << r1.distanceTo(r2)
                << " from " << r2.name << '\n';
    }
  }

  for(auto r: fleet)
    std::cout << r.x() << std::endl;


  [[maybe_unused]] auto dist = rob.distanceTo(target);

  //auto robot{Robot{.x_ = -1}};
  //robot.print();




  Matrix M(4, 3);
  auto [r,c] = M.dim();








}
