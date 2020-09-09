#include <iostream>
#include <tuple>
#include <math.h>

using namespace std;


namespace ecn
{
int f(int x)
{
  cout << "Calling f int from ecn namespace" << endl;
  return x - 1;
}
}


int f(const int &x)
{
  cout << "Calling f int" << x << endl;

  return x;
}

double f(double x)
{
  cout << "Calling f double" << endl;
  x = x+ 1;
  return x;
}


int main()
{
  int x(4);
  f(x);
  std::cout << x << std::endl;


}
