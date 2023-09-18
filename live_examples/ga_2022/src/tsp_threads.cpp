#include <travel.h>
#include <iostream>
#include <ga_opt.h>
#include <chrono>
#include <thread>
#include <future>

using Clock = std::chrono::high_resolution_clock;
using namespace std::chrono;
using namespace std::chrono_literals;

int main()
{
  Travel::load();

  const auto start{Clock::now()};

  const auto cpus{6}; // less than std::thread::hardware_concurrency()
  std::vector<std::future<Travel>> runs;

  for(int i = 0; i < cpus; ++i)
    runs.push_back(std::async([i]()
    {
      std::cout << "Run #" << i << " launched" << std::endl;
      const auto solution{genetic<Travel>()};
      std::cout << "Run #" << i << " done" << std::endl;
      return solution;
    }));

  std::vector<Travel> solutions;
  solutions.reserve(cpus);
  for(auto &run: runs)
  {
    run.wait();
    solutions.push_back(run.get());
  }

  const auto solution = std::min_element(solutions.begin(), solutions.end());

  const auto end{Clock::now()};

  solution->print();
  std::cout << duration_cast<milliseconds>(end-start).count() << " ms" << std::endl;

  solution->plot();
}
