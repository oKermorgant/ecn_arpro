#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include <tuple>


int main(int argc, char ** argv)
{
    /*std::cout << "Hello world!!" << std::endl;

    std::cout << "You have " << argc << " arguments  :" << std::endl;
    for(unsigned int i=0;i<argc;++i)
        std::cout << "  - " << argv[i] << std::endl;
    */

  int x = 5;
  int* p = new int(4);
  p = &x;

std::cout << *p << std::endl;
  delete p;
//std::cout << *p << std::endl;
  std::cout << x << std::endl;


}
