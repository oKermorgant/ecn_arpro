#include <xy.h>
#include <genetic.h>
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using Clock = std::chrono::steady_clock;

int main()
{
  const auto start = Clock::now();
  auto solution = genetic<XY>(500);

  const auto dur_ms = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count();

  solution.print();

  std::cout << "Found in " << dur_ms << " ms\n";



}
