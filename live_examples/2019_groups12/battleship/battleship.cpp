#include "player.h"

int main()
{
    
  Player p1, p2;

  while(true)
  {
    p2.display();
    if(p1.shoot(p2))
      break;

    p1.display();
    if(p2.shoot(p1))
      break;
  }
}
