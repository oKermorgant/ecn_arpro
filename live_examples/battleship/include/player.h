#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <boat.h>


class Player
{
  // TODO grid with boats ???
  std::array<
            std::array<Cell,10>,
            10
            > grid;


public:
  Player();


  void target(Player other);

  void display();

  bool stillAlive()
  {
    // TODO
    return false;
  }



};

#endif // PLAYER_H
