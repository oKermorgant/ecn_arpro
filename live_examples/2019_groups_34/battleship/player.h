#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "cell.h"

class Player
{
private:
  // a 10 x 10 grid of Cell's
  std::array<std::array<Cell, 10>, 10> grid;

public:
  Player();

  void shoot(Player opponent);

  void display();

  bool hasLost();

};

#endif // PLAYER_H
