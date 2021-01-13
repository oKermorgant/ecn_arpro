#include "xy.h"
#include "ga.h"
#include <iostream>

int main()
{
  auto xy = ga<XY>();
  xy.print();

  std::cout << "Created " << xy.created <<
               ", compared " << comparisons << std::endl;
}


