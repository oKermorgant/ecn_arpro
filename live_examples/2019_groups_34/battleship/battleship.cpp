#include "player.h"


// battleship.cpp

int main()
{
  Player p1, p2;

  while(true)
  {
    p2.display();
    p1.shoot(p2);
    if(p2.hasLost())
      break;

    p1.display();
    p2.shoot(p1);
    if(p1.hasLost())
      break;
  }

    
}
