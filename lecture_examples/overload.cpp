#include <iostream>

int Square(int x)
{
  std::cout << "inside Square(int)" << std::endl;
  return x*x;
}

double Squared(double x)
{
  std::cout << "inside Square(double)" << std::endl;
  return x*x;
}

void print(const int &v)
{
  std::cout << v << std::endl;
}

int main()
{
  Square(2);
  //std::cout << Square(3) << std::endl;;
  std::cout << Square(3.14) << std::endl;

  std::cout << std::abs(3.14) << std::endl;


}
