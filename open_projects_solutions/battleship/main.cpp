#include "player.h"

using std::cout;
using std::endl;

int main()
{
    Player p1("Player"), p2("Computer", false);

    while(true)
    {
        p1.Print(p2);
        if(p1.Shoot(p2))
        {
            p1.wins();
            break;
        }

        if(p2.Shoot(p1))
        {
            p2.wins();
            break;
        }
    }
}
