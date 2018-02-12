#ifndef TICTACTOE_CONFIG_H
#define TICTACTOE_CONFIG_H


#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */

// This class defines what is a configuration for the Tic Tac Toe game

class TicTacToe
{
public:
    TicTacToe()
    {
        moves.reserve(9);
        moves.clear();
        turn_count = 1;
        combos = {{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{7,5,3}}; // winning combos
        positions.reserve(5);
    }

    void GetAlphaBeta(int &a, int &b)
    {
        a=-200;
        b=200;
    }

    // check if the game is finished, does not check for a winner
    bool Over()
    {
        // it is finished as soon as 9 moves have been played
        return moves.size() == 9;
    }

    inline bool NotContains(std::vector<unsigned int> &v, unsigned int i)
    {
        return std::find(v.begin(), v.end(), i) == v.end();
    }


    // returns winner (1 or 2) or 0 if no winner
    int Winner()
    {
        for(unsigned int player: {1,2})
        {
            positions.clear();
            for(unsigned int i=player-1;i<moves.size();i+=2)
                positions.push_back(moves[i]);

            // test if any combo in the positions
            for(auto &combo: combos)
            {
                bool win = true;
                for(auto i: combo)
                    if(NotContains(positions, i))
                        win = false;
                if(win)
                    return player;
            }
        }
        return 0;
    }

    // prints the game
    void Print()
    {
        std::vector<std::string> legend = {".", "x", "o"};
        std::vector<unsigned int>  grid(9, 0);
        unsigned int player = 1;
        for(auto move: moves)
        {
            grid[move-1] = player;
            player = 3-player;
        }

        for(unsigned int i=0;i<3;++i)
        {
            std::cout << "  ";
            for(unsigned int j=0;j<3;++j)
                std::cout << legend[grid[3*i+j]] << "  ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // return the list of available moves
    std::vector<unsigned int> AvailableMoves()
    {
        std::vector<unsigned int> avail;
        for(unsigned int i=1;i<10;++i)
        {
            if(NotContains(moves, i))
                avail.push_back(i);
        }
        return avail;
    }

    void MakeMove(unsigned int move)
    {
        moves.push_back(move);
        turn_count++;
    }

    void CancelMove(unsigned int move)
    {
        moves.pop_back();
        turn_count--;
    }


    void HumanInput(unsigned int player, bool random = false)
    {
        unsigned int i = 10;
        if(random)
        {
            i = (rand() % 9)+1;
        }
        else
        {
            while(i < 1 || i > 9 || !NotContains(moves, i))
            {
                std::cout << "Player " << player << "'s turn, enter a number in [1,9]: ";
                std::cin >> i;
            }
        }
        MakeMove(i);
    }

    bool MustThink()    // returns true unless it is the first turn, in this case plays the center cell
    {
        if(moves.size())
            return true;

        MakeMove(5);
        return false;
    }

protected:
    std::vector<unsigned int> moves;
    unsigned int turn_count;
    std::vector<std::vector<unsigned int> > combos;
    std::vector<unsigned int> positions;
};
#endif
