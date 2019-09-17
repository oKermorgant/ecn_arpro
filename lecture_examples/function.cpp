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


int f(int x)
{
  cout << "Calling f int" << endl;
  x = x+ 1;

  return x;
}

double f(double x)
{
  cout << "Calling f double" << endl;
  x = x+ 1;
  return x;
}

std::tuple<bool,double> square_root(double x)
{
  if(x < 0)
    return {false,0};
  return {true, sqrt(x)};
}




int main()
{
  f(4);
  f(3.14);
  ecn::f(4);

  for(auto x: {-2, 2})
  {
    if(auto [ok,y] = square_root(x);ok)
      std::cout << "Square root of " << x << " is " << y << std::endl;
    else
      std::cout << x << " has no square root" << endl;
  }

}
