#include <iostream>
#include <map>
#include <chrono>

using namespace std;


using Clock = chrono::steady_clock;

inline int milliseconds_since(const Clock::time_point &start)
{
  return chrono::duration_cast<chrono::milliseconds>(Clock::now()-start).count();
}

int fibo(int n)
{
  if(n <= 1)
    return n;
  return fibo(n-1) + fibo(n-2);
}

int fibo_detailed(int n)
{
  if(n <= 1)
    return n;
  std::cout << "computing fibo(" << n << ")\n";
  return fibo_detailed(n-1) + fibo_detailed(n-2);
}

int fibo_cached(int n)
{
  static std::map<int,int> cache;
  if(n <= 1)
    return n;

  auto &cached{cache[n]};
  if(!cached) // actually compute if 0 (was not in cache)
    cached = fibo_cached(n-1) + fibo_cached(n-2);
  return cached;
}

int fibo_cached_detailed(int n)
{
  static std::map<int,int> cache;
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
}

int main()
{
  // recursive, without cache
  auto start{Clock::now()};
  std::cout << fibo(40);
  std::cout << " / took " << milliseconds_since(start) << " ms" << std::endl;

  // recursive, with cache
  start = Clock::now();
  std::cout << fibo_cached(40);
  std::cout << " / took " << milliseconds_since(start) << " ms" << std::endl;

  fibo_detailed(10);
  fibo_cached_detailed(10);




}
