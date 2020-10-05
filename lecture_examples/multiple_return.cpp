#include <tuple>
#include <math.h>
#include <iostream>

std::tuple<bool, double> square_root(double x)
{
  if(x < 0)
    return {false, 0};
  return {true, sqrt(x)};
}

int main()
{
  for(auto x: {-2., 2., 3.14})
  {
    std::cout << "Testing for " << x << ": ";

    if(auto [valid, sqr] = square_root(x); valid)
    {
        std::cout << "square root is " << sqr << std::endl;
    }
     else
    {
      std::cout << "square root is not valid" << std::endl;
    }


  }

}
