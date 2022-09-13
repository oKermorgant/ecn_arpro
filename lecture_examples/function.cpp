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

void squared(int &x)
{
  x *= x;
}

void squared(int x)
{
  x *= x;
}

int main(int argc, char** argv)
{
  int x(4);

  auto func = [](bool ok)
  {
    if(ok) return .1;return .2;
  };

  sqrt(argc-4);

  f(x);

  //std::cout << x << std::endl;

  int a{2};
  cout << a << endl;

}
