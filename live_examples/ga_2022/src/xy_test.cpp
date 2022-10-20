#include "rand_range.h"
#include "xy.h"
#include <iostream>
int main()
{

  XY xy1, xy2;

  auto xy3{xy1.crossAndMutate(xy2)};

  xy1.print();
  xy2.print();
  xy3.print();



}
