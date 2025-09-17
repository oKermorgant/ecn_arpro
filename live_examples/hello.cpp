#include <iostream>

bool isOdd(int n)
{
  // TODO do the function
  return true;
}



int main()
{

  for(auto i: {0,1,2,3})
  {
    std::cout << i << " is odd? " << std::boolalpha << " " << isOdd(i) << '\n';
  }



std::cout << "Hello, World!" << std::endl;
}
