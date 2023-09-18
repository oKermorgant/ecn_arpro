#include <iostream>
#include <map>
#include <chrono>
#include "large_number.h"
#include "scoped_timer.h"

using namespace std;

//#define detailed

LargeNumber fibo(LargeNumber n)
{
#ifdef detailed
  cerr << "computing f(" << n << ")\n";
#endif
  if(n < 2)
    return n;
  return fibo(n-1) + fibo(n-2);
}

LargeNumber fibo_cached(LargeNumber n)
{
  static std::unordered_map<LargeNumber,LargeNumber,LargeNumber::hash> cache;

  if(n < 2)
    return n;

  auto &cached{cache[n]};
  if(cached.isNull()) // actually compute if 0 (was not in cache)
  {
    cached = fibo_cached(n-1) + fibo_cached(n-2);
  }
  else
  {
#ifdef detailed
    cerr << "already know f(" << n << ")\n";
#endif
  }
  return cached;
}


void do_raw(int n)
{
  ScopedTimer timer(std::to_string(n) + " not cached");
  cout << "f(" << n << ") = " << fibo(n) << endl;
}

void do_cached(int n)
{
  ScopedTimer timer(std::to_string(n) + " cached");
  cout << "f(" << n << ") = " << fibo_cached(n) << endl;
}


int main()
{
  do_raw(15);
  do_raw(20);
  do_raw(30);
  do_cached(15);
  do_cached(20);
  do_cached(30);
  do_cached(100);
  do_cached(10000);
}
