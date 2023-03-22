#ifndef SCOPED_TIMER_H
#define SCOPED_TIMER_H

#include <chrono>
#include <string>
#include <iostream>

class ScopedTimer
{
  using Clock = std::chrono::steady_clock;
  Clock::time_point start;
  std::string msg;
public:
  inline explicit ScopedTimer(const std::string &msg) : start{Clock::now()}, msg{msg} {}
  inline ~ScopedTimer()
  {
    std::cout << msg << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
  }


};

#endif // SCOPED_TIMER_H
