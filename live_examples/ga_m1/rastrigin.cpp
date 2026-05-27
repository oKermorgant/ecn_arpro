#include <xy.h>
#include <ga.h>

#include <chrono>

namespace chrono = std::chrono;
using Clock = chrono::high_resolution_clock;

int main()
{

  const auto start{Clock::now()};
  optimize().print();
  const auto end{Clock::now()};

  std::cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms" << std::endl;




}
