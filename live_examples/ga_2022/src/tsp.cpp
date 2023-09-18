#include <travel.h>
#include <iostream>
#include <ga.h>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using namespace std::chrono;
using namespace std::chrono_literals;

int main()
{
  Travel::load();

  const auto start{Clock::now()};
  const auto solution{genetic<Travel>()};
  const auto end{Clock::now()};

  solution.print();

  std::cout << duration_cast<milliseconds>(end-start).count() << " ms" << std::endl;

  solution.plot();
}
