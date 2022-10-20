#include <iostream>
#include <map>
#include <chrono>
#include <fibonacci_helpers.h>

using namespace std;

using LargeNumber = fibonacci::LargeNumber<400>;


using Clock = chrono::steady_clock;

inline int milliseconds_since(const Clock::time_point &start)
{
  return chrono::duration_cast<chrono::milliseconds>(Clock::now()-start).count();
}

LargeNumber fibo(LargeNumber n)
{
  cout << "computing f(" << n << ")\n";
  if(n.lessThan2())
    return n;
  return fibo(n.minusOne()) + fibo(n.minusTwo());
}

/*
LargeNumber fibo_detailed(LargeNumber n)
{
  if(n <= 1)
    return n;
  std::cout << "computing fibo(" << n << ")\n";
  return fibo_detailed(n-1) + fibo_detailed(n-2);
}*/


LargeNumber fibo_cached(LargeNumber n, bool show_cache_size = false)
{
  static std::unordered_map<LargeNumber,LargeNumber,LargeNumber::hash> cache;
  //static std::map<LargeNumber,LargeNumber> cache;
  if(show_cache_size)
    std::cout << "Current cache is " << cache.size() << std::endl;


  if(n.lessThan2())
    return n;

  auto &cached{cache[n]};
  if(cached == 0) // actually compute if 0 (was not in cache)
    cached = fibo_cached(n.minusOne()) + fibo_cached(n.minusTwo());
  return cached;
}

/*

LargeNumber fibo_cached_detailed(LargeNumber n)
{
  static std::map<LargeNumber,LargeNumber> cache;
  if(n <= 1)
    return n;

  auto &cached{cache[n]};
  std::cout << n;
  if(!cached) // actually compute if 0 (was not in cache)
  {
    std::cout << " not in cache\n";
    cached = fibo_cached_detailed(n-1) + fibo_cached_detailed(n-2);
  }
  else
  {
    std::cout << " in cache\n";
  }
  return cached;
}*/

int main()
{
  auto start{Clock::now()};

  fibo_cached(100);

  cout << fibo_cached(1000) << std::endl;


  std::cout << " / took " << milliseconds_since(start) << " ms" << std::endl;



}
  /*


  return 0;
  // recursive, with cache
  start = Clock::now();
  auto n{1000};
  std::cout << "f(" << n << ") = " << fibo_cached(n);
  std::cout << " / took " << milliseconds_since(start) << " ms" << std::endl;

  std::cout << LargeNumber(0) << " " << LargeNumber(10) << " " << LargeNumber(1) << std::endl;

  //fibo_detailed(10);
  fibo_cached(10, true);




}

*/
