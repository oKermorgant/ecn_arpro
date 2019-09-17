#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "cell.h"
#include <map>

// a Player class that may be human or not

class Player
{
public:
    Player(std::string _name, bool _human = true);

    // the value at a given grid position
    inline Cell& cell(unsigned int row, unsigned int col)
    {
        if( row > 9 || col > 9)
        {
            std::cout << "Wrong row/column given: "<< row << ", "<< col << std::endl;
            return grid[0];
        }
        return grid[10*row + col];
    }

    Cell cell(unsigned int row, unsigned int col) const
    {
        if( row > 9 || col > 9)
        {
            std::cout << "Wrong row/column given: "<< row << ", "<< col << std::endl;
            return grid[0];
        }
        return grid[10*row + col];
    }

    // print this grid and the one of the other player
    void Print(const Player &other);

    // shoot at the other
    bool Shoot(Player &other);

    void wins() {std::cout << name << " wins!"<< std::endl;}


protected:

    bool human;
    std::string name;
    std::array<Cell, 100> grid;
    std::map<char,uint> boats;

    // for computer: history of passed shots
    std::vector<uint> hist;

    // print a grid line
    std::string PrintRow(uint r) const;
};




#endif // PLAYER_H
