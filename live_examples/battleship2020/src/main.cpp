#include <player.h>

int main()
{

  Player p1, p2(false);

  while(true)
  {
    if(p1.hasBoats())
      p1.shoot(p2);
    else
      break;

    if(p2.hasBoats())
      p2.shoot(p1);
    else
      break;
  }

}
