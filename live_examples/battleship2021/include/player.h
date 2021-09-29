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

  bool isAlive()
  {
    return true;
  }



private:
  std::array<std::array<Cell, 10>, 10> grid;
  void placeBoats();
};

#endif // PLAYER_H
