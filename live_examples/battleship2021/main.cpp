#include <player.h>

int main()
{
  Player p1, p2;

  while(p1.isAlive() || p2.isAlive())
  {
    p1.display();
    p1.shoot(p2);
    if(p2.isAlive())
    {
      p2.display();
      p2.shoot(p1);
    }
    break;
  }


}
