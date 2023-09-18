#include <xy.h>
#include <iostream>

using std::cout;
using std::endl;


int main()
{
  XY xy1, xy2;
  xy1.randomize();
  xy2.randomize();
  xy1.print();
  xy2.print();

  for(int i = 0; i < 10; ++i)
    xy1.cross(xy2).print();



}
