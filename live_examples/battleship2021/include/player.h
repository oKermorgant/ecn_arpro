#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <array>
#include <cell.h>

class Player
{
public:
  Player();

  void display();

  void shoot(Player &other);

  bool isAlive();

private:

  std::array<std::array<Cell, 10>, 10> grid;

  int live_boats{0};

  void placeBoats();

  void hitCell(int row, int col);

  Cell at(int row, int col)
  {
    return grid[row][col];
  }
};

#endif // PLAYER_H
