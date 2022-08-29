#include <player.h>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main()
{

  const auto start(std::chrono::steady_clock::now());

  Player p1, p2;

  while(p1.isAlive() && p2.isAlive())
  {
    p1.shoot(p2);
    p2.display();
    if(p2.isAlive())
    {      
      p2.shoot(p1);
      p1.display();
    }
  }

  const auto end(std::chrono::steady_clock::now());
  std::cout << "Elapsed time: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " mus" << std::endl;
}
