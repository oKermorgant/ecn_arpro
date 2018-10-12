#include "player.h"

int main()
{
Player p1(true), p2(false);

//while(p1.alive() && p2.alive())
{
    p2.display();
    p1.shoot(p2);
    if(p2.alive())
    {
        p1.display();
        p2.shoot(p1);
    }
}


}
