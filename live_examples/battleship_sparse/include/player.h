#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <boat.h>

class Player
{
 private:
  void placeBoats();

  std::vector<Boat> boats;


public:
  Player();

  void display();

  void shoot(Player other);

  bool stillAlive()
  {
    return true;
  }




};

#endif // PLAYER_H
