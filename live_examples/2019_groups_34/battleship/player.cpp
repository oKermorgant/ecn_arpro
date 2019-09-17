#include "player.h"
#include <iostream>
#include <vector>

Player::Player()
{
  const std::vector<std::pair<uint, char>> boats{{5, 'A'}, {4, 'C'}, {3, 'D'}, {3, 'S'}, {2, 'M'}};

  for(const auto &boat: boats)
  {
    const auto length = boat.first;
    const auto type = boat.second;



  }

}


void Player::shoot(Player opponent)
{

}

void Player::display()
{
  std::cout << "  0 1 2 3 4 5 6 7 8 9\n";

  for(uint row = 0; row < 10; ++row)
  {
    // display row number
    std::cout << row << " ";

    // loop through columns
    for(uint col = 0; col < 10; ++col)
      std::cout << grid[row][col].display(false) << " ";

    std::cout << std::endl;
  }
}

bool Player::hasLost()
{

  return true;
}
