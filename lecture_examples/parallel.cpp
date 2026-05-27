#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <random>

#include <chrono>

struct ScopedTimer
{
  using Clock = std::chrono::high_resolution_clock;
  Clock::time_point start;
  std::string msg;
  ScopedTimer(const std::string &msg) : start{Clock::now()}, msg{msg} {}
  ~ScopedTimer()
  {
    std::cout << msg << ": " << std::chrono::duration_cast<std::chrono::microseconds>
                                (Clock::now()-start).count() << " µs" << std::endl;
  }
};

using namespace std;

// function that set its argument to the square
auto square(int &val){val *= val;};

int main()
{


  std::vector<int> numbers_base(1000000);
  // fill with 0..999
  {
    ScopedTimer timer("filling");
    std::iota(numbers_base.begin(), numbers_base.end(), 0);
  }


  // call this function, non-parallel
  {
    auto numbers{numbers_base};
    ScopedTimer timer("squaring, non-par");
    std::ranges::for_each(numbers, square);
  }

  // call this function, parallel
  {
    auto numbers{numbers_base};
    ScopedTimer timer("squaring, par");
    std::for_each(std::execution::par,
                  numbers.begin(), numbers.end(),
                  square);
  }

  // randomize and sort, non-parallel
  auto numbers{numbers_base};
  std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine());
  const auto copy{numbers}; // keep original order for comparison
  {
    ScopedTimer timer("sorting, non-par");
    std::sort(numbers.begin(), numbers.end());
  }

  // randomize and sort, parallel
  numbers = copy; // restore original order
  {
    ScopedTimer timer("sorting, par");
    std::sort(std::execution::par, numbers.begin(), numbers.end());
  }

}
