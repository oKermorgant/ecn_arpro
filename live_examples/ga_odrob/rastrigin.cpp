#include <xy.h>
#include <ga.h>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
namespace chrono = std::chrono;

int main()
{
  const auto start{Clock::now()};
  optimize().print();
  const auto end{Clock::now()};

  std::cout << chrono::duration_cast<chrono::milliseconds>((end-start)).count()
            << " ms" << std::endl;



}
