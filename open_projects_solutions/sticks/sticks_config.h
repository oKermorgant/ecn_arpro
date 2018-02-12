#ifndef STICKS_CONFIG_H
#define STICKS_CONFIG_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */

// This class defines what is a configuration for the 21 sticks game

class Sticks
{
public:
    Sticks(int start = 21)
    {
        sticks = start;
        turn_count = 0;
    }


    inline bool NotContains(std::vector<int> &v, int i)
    {
        return std::find(v.begin(), v.end(), i) == v.end();
    }

    void GetAlphaBeta(int &a, int &b)
    {
        a=-200;
        b=200;
    }

    bool Over()
    {
        return !sticks;
    }

    // returns winner (1 or 2) or 0 if no winner
    int Winner()
    {
        if(Over())
            return 1+(turn_count % 2);

        return 0;
    }

    // prints the game
    void Print()
    {
        std::cout << sticks << " sticks remaining" << std::endl;
            for(int i=0;i<sticks;++i)
                std::cout << " |";
            std::cout << std::endl;

    }

    // return the list of available moves
    std::vector<int> AvailableMoves()
    {
        std::vector<int> avail;
        for(int i=1;i<=std::min(sticks, 3);++i)
            avail.push_back(i);
        return avail;
    }

    void MakeMove(int move)
    {
        turn_count++;
        sticks -= move;
    }

    void CancelMove(int move)
    {
        sticks += move;
        turn_count--;
    }


    void HumanInput(unsigned int player, bool random = false)
    {
        int i;
        int max_move = std::min(sticks, 3);
        if(random)
        {
            i = rand() % max_move +1;
        }
        else
        {
            auto avail = AvailableMoves();
            while(true)
            {
                std::cout << "Player " << player << "'s turn, enter a number in [1,3]: ";
                std::cin >> i;
                if(i > 0 && i <= max_move && !NotContains(avail, i))
                    break;
            }
        }
        MakeMove(i);
    }

    // returns true in this game
    bool MustThink()
    {
        return true;
    }

protected:
    int sticks;
    unsigned int turn_count;
};


#endif // STICKS_GAME_H
