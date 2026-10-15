#include <iostream>
#include <point.h>

#include <ga.h>
#include <chrono>



int main()
{

  Point xy{};
  xy.mutate();

  using Clock = std::chrono::high_resolution_clock;

  const auto start{Clock::now()};

  auto best = optimize();

  const auto end{Clock::now()};
  best.print();
  std::cout << "Took "
            <<   std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " mus" << std::endl;

}
