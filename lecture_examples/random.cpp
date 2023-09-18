#include <iostream>

// old way - easy to use
#include <stdlib.h>
#include <time.h>

// modern way
#include <random>

int main()
{

  // old way: rand() generates integers between 0 and RAND_MAX-1
  std::cout << "Old way" << std::endl;
  // seed of the random numbers generator is current time
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
  std::cout << "\nModern way" << std::endl;
  std::random_device device;                // get a random seed
  std::mt19937 rand_generator(device());    // actual generator, from seed

  // random integers between 1 - 100
  std::uniform_int_distribution<> dice100(1, 100);
  for(int i = 0; i < 10; ++i)
    std::cout << dice100(rand_generator) << " ";
  std::cout << std::endl;

  // random double between -1 - 1
  std::uniform_real_distribution<> minus1_1(-1, 1);
  for(int i = 0; i < 10; ++i)
    std::cout << minus1_1(rand_generator) << " ";
  std::cout << std::endl;

  // Gaussian noise of std = 1 centered on 2
  std::normal_distribution<> gaussian(2, 1);
  for(int i = 0; i < 10; ++i)
    std::cout << gaussian(rand_generator) << " ";
  std::cout << std::endl;





}
