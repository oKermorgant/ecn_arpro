#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{
  // all combinations of 2 ints from 0 to 100
  unsigned int i;
  for(i=0; i < 99; i++)
  {
    for(unsigned int j=i+1; j < 100; j++)
      std::cout << i << " and " << j << std::endl;
  }
}
