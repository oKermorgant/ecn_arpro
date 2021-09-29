#include <iostream>

#include <random>

int main()
{


  std::random_device device;
std::mt19937 generator(device());
std::normal_distribution<> dice(1, 6);

for(int i = 0; i < 20; ++i)
  std::cout << dice(generator) << std::endl;

  /*
srand(time(nullptr));
for(int i = 0; i < 20; ++i)
  std::cout << 1+rand() % 6 << std::endl;
*/

}
