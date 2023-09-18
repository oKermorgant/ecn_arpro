#include <iostream>
#include <vector>
#include <algorithm>

inline bool isOdd(int i)
{
  return i % 2 == 1;
}


int main(int argc, char** argv)
{

  std::vector<int> v = {1,2,3,4,5,6,7,8,9};

  //std::cout << std::boolalpha << isOdd(v[1]) << std::endl;

  if(std::all_of(v.begin(), v.end(), [](auto i)
  {
                   return i % 2 == 0;
}) > 0)
  {


  }






}

