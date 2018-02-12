#ifndef FOURINAROW_CONFIG_H
#define FOURINAROW_CONFIG_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */

// This class defines what is a configuration for the 4-in-a-row game

class FourInARow
{
public:
    FourInARow()
    {
        grid = std::vector<std::vector<unsigned int> >(6, std::vector<unsigned int>(7,0));
        turn_count = 0;
        positions.reserve(5);
    }

    void GetAlphaBeta(int &a, int &b)
    {
        a=-200;
        b=200;
    }

    bool Over()
    {
        return NotContains(grid[0], 0);
    }

    inline bool NotContains(std::vector<unsigned int> &v, unsigned int i)
    {
        return std::find(v.begin(), v.end(), i) == v.end();
    }

    // returns winner (1 or 2) or 0 if no winner
    int Winner()
    {
        if(turn_count < 6)
            return 0;

        int dx = 0, dy = 0, count;
        for(unsigned int player: {1,2})
        {
            for(int i=0;i<6;++i)
            {
                for(int j=0;j<7;++j)
                {
                    if(grid[i][j] == player)
                    {
                        for(int d = 0;d < 4;++d)
                        {
                            count = 1;
                            switch(d)
                            {
                            case 0:
                                dx = 1;
                                dy = 0;
                                break;
                            case 1:
                                dx = 0;
                                dy = 1;
                                break;
                            case 2:
                                dx = dy = 1;
                                break;
                            case 3:
                                dx = -1;
                                dy = 1;
                                break;
                            }
                            for(int k=1;k<4;++k)
                            {
                                if(i+k*dx>=0 && i+k*dx<6 && j+k*dy>=0 && j+k*dy < 7)
                                {
                                    if(grid[i+k*dx][j+k*dy] == player)
                                    {
                                        count++;
                                    }
                                    else
                                        break;
                                }
                            }
                            if(count == 4)
                                return player;
                        }
                    }
                }
            }
        }
        return 0;
    }

    // prints the game
    void Print()
    {
        std::vector<std::string> legend = {".", "x", "o"};

        std::cout << "\n  1  2  3  4  5  6  7\n";
        
        for(unsigned int i=0;i<6;++i)
        {
            std::cout << "  ";
            for(unsigned int j=0;j<7;++j)
                std::cout << legend[grid[i][j]] << "  ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // return the list of available moves
    std::vector<unsigned int> AvailableMoves()
    {
        std::vector<unsigned int> avail;
        for(unsigned int i=0;i<7;++i)
        {
            if(grid[0][i] == 0)
                avail.push_back(i+1);
        }
        return avail;
    }

    void MakeMove(unsigned int move)
    {
        turn_count++;
        for(int i=5;i!=-1;--i)
        {
            if(!grid[i][move-1])
            {
                grid[i][move-1] = 2-(turn_count%2);
                break;
            }
        }
    }

    void CancelMove(unsigned int move)
    {
        for(int i=0;i<6;++i)
        {
            if(grid[i][move-1])
            {
                grid[i][move-1] = 0;
                break;
            }
        }
        turn_count--;
    }


    void HumanInput(unsigned int player, bool random = false)
    {
        unsigned int i = 10;
        if(random)
        {
            i = (rand() % 7)+1;
        }
        else
        {
            auto avail = AvailableMoves();
            while(true)
            {
                std::cout << "Player " << player << "'s turn, enter a number in [1,7]: ";
                std::cin >> i;
                if(i > 0 && i < 8 && !NotContains(avail, i))
                    break;
            }
        }
        MakeMove(i);
    }

    // returns true unless it is the first turn, in this case plays 4th column
    bool MustThink()
    {
        if(turn_count)
            return true;

        MakeMove(4);
        return false;
    }

protected:
    std::vector<std::vector<unsigned int> > grid;
    unsigned int turn_count;
    std::vector<unsigned int> positions;
};
#endif
