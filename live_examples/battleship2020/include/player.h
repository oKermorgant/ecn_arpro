#ifndef PLAYER_H
#define PLAYER_H


#include <boat.h>
#include <array>
#include <vector>

class Player
{
public:
  Player(bool human = true);

  void display(const Player &other);
  void shoot(Player &other);

  bool hasBoats() const
  {
    return live_boats;
  }

private:
  std::array<std::array<Boat, 10>, 10> grid;
  const bool is_human;
  int live_boats = 0;

  void sink(int row, int col);

  void displayLine(int line) const;

  std::vector<Boat *> randomPlacement(int length);

  void registerShot(int row, int col);



};

#endif // PLAYER_H
