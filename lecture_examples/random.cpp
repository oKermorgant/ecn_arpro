#include <iostream>

// old way - easy to use
#include <stdlib.h>
#include <time.h>

// modern way
#include <random>

int main()
{

  // old way: rand combined with RAND_MAX
  // seed of the random numbers generator
  srand(time(0));
  for(int i = 0; i < 10; ++i)
  {
    // integers between 0 and 100
    std::cout << rand() % 101 << " ";
  }
  std::cout << std::endl;

  for(int i = 0; i < 10; ++i)
  {
    // double between -1 and 1
    double between_0_1 = ((double) rand())/(RAND_MAX-1);
    std::cout << -1 + 2*between_0_1 << " ";
  }
  std::cout << std::endl;
  // end of the old way


  // modern way
  std::random_device device;          // equivalent of srand
  std::mt19937 generator(device());   // equivalent of rand

  // random integers between 1 - 100
  std::uniform_int_distribution<> dice100(1, 100);
  for(int i = 0; i < 10; ++i)
    std::cout << dice100(generator) << " ";
  std::cout << std::endl;

  // random double between -1 - 1
  std::uniform_real_distribution<> minus1_1(-1, 1);
  for(int i = 0; i < 10; ++i)
    std::cout << minus1_1(generator) << " ";
  std::cout << std::endl;

  // Gaussian noise of std = 1 centered on 2
  std::normal_distribution<> gaussian(2, 1);
  for(int i = 0; i < 10; ++i)
    std::cout << gaussian(generator) << " ";
  std::cout << std::endl;





}
