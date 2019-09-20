#ifndef PLAYER_H
#define PLAYER_H
#include <array>
#include "cell.h"
class Player
{
private:

  std::array<Cell,100> grid;

  Cell& cell(uint row, uint col)
  {
    return grid[row + 10*col];
  }


public:
  Player();

  void display();

  bool shoot(Player & other);

};

#endif // PLAYER_H
