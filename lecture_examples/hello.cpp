#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

class Test
{
public:
  int i_;

  void func(int _i)
  {
   if(_i == 1)
   {
    int i;
   }
  }

};

int main(int argc, char ** argv)
{
    std::cout << "Hello world!!" << std::endl;

    std::cout << "You have " << argc << " arguments  :" << std::endl;
    for(unsigned int i=0;i<argc;++i)
        std::cout << "  - " << argv[i] << std::endl;


    std::cout << abs(-2.3) << std::endl;
}
