#include "xy.h"
#include "ga.h"
#include <chrono>

int main()
{

  auto start = std::chrono::system_clock::now();

  std::array<XY,10> bests;
  for(auto &indiv: bests)
    genetic_algo(indiv);
  const auto best = *std::min_element(bests.begin(), bests.end());

  auto end = std::chrono::system_clock::now();
  best.print();

  std::chrono::duration<double> elapsed_seconds(end-start);
  std::cout << "Found in " << elapsed_seconds.count()
            << " s" << std::endl;
}
