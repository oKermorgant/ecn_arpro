#include <iostream>
#include <tuple>
#include <numeric>
#include <vector>
#include <algorithm>

#include <sstream>

const int debug = 0;

bool isEven(int n)
{
  return n%2 == 0;
}

int main()
{
  std::vector<int> v{0,2,2,6,4};

  auto x{9};
  if(x = 7)
  {


  }

  std::cout <<
               std::all_of(v.begin(), v.end(), [](auto i)
  {
    return i % 2 == 0;
  })
            << std::endl;


  if(std::find(v.begin(), v.end(), 3) != v.end())
    std::cout << "there is a 3: "<< std::endl;







  ;}
