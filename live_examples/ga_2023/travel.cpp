#include <travel.h>
#include <genetic.h>
#include <iostream>
#include <chrono>
#include <filesystem>

using Clock = std::chrono::high_resolution_clock;

using std::cout;
using std::endl;
namespace fs = std::filesystem;


int main()
{
  Travel::load();

  const auto start = Clock::now();
  const auto solution = genetic<Travel>(500);
  const auto end = Clock::now();

  solution.print();

  const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
      (end - start);

  std::cout << duration.count() << " ms" << std::endl;

  solution.plot();


}
