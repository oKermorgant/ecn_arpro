#include <xy.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include <genetic.h>

int main()
{

  const auto best = geneticOptim<XY>();
  best.print();

}
