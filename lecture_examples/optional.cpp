#include <iostream>
#include <optional>
#include <math.h>

std::optional<double> squareRoot(double x)
{
  if(x < 0)
    return {};
  return sqrt(x);
}


int main()
{

  for(auto x: {2, -1})
  {
    if(const auto root{squareRoot(x)}; root.has_value())
    { 
      std::cout << "square root of " << x << " is " << root.value() << std::endl;
    }
    else
      std::cout << x << " has no square root" << std::endl;
  }

  std::optional<std::string> none;
  std::cout << none.value_or("default value") << std::endl;
  none = "actual value";
  std::cout << none.value_or("default value") << std::endl;




}
