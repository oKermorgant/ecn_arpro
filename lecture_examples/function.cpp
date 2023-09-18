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

void squared(int x)
{
  x *= x;
}


void squared_ref(int &x)
{
  x *= x;
}

struct TwoDoubleandAString
{
  double x, y;
  std::string name;
};

TwoDoubleandAString getCoord()
{
  return {0.,1., ""};
}




int main(int argc, char** argv)
{
  int x(4);

  squared(x);
  squared_ref(x);


  std::cout << x << std::endl;









  auto func = [](bool ok)
  {
    if(ok) return .1;return .2;
  };

  f(x);

  //std::cout << x << std::endl;


}
