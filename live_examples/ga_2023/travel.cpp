#include <travel.h>
#include <genetic.h>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
  Travel::load();

  for(auto &city: Travel::cities)
    std::cout << city << " ";

  Travel t1, t2;




  auto solution = genetic<Travel>(500);

  //std::cout << (t1 < t2) << std::endl;

}
