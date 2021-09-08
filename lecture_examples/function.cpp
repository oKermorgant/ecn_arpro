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



int f(const int &other)
{
  //cout << "Calling f const &int" << x << endl;

  return other;
}

int main()
{
  int x(4);

  f(x);

  std::cout << x << std::endl;


}
