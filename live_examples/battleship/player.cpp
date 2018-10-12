#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Player::Player(bool is_human)
{
    human = is_human;
    grid.resize(100, 0);

    srand(time(0));
    const vector<int> sizes = {2,3,3,4,5};

    for(int k = 0; k < sizes.size() ;++k)
    {
        bool empty = false;
        while(!empty)
        {
            const int ori = rand() % 2;
            int r, c;
            if(ori == 0)
            {
                r = rand() % (10 - sizes[k]);
                c = rand() % 10;
            }
            else
            {
                c = rand() % (10 - sizes[k]);
                r = rand() % 10;
            }
            empty = true;
            for(int m = 0; m < sizes[k]; ++m)
            {
                if(cell(r + (1-ori)*m, c + ori*m))
                    empty = false;
            }

            if(empty)
                for(int m = 0; m < sizes[k]; ++m)
                    cell(r + (1-ori)*m, c + ori*m) = k+2;
        }
    }

}

bool Player::alive()
{
    return true;
}

void Player::shoot(Player other)
{

}

void Player::display()
{
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
    for(int r = 0; r < 10; ++r)
    {
        cout << r << " ";
        for(int c = 0; c < 10; ++c)
            cout <<cell(r,c) << " ";
        cout << endl;
    }
    cout << endl << endl;
}
