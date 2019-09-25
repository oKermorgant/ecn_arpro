#include "player.h"
#include <iostream>
#include <vector>
#include <algorithm>

Player::Player()
{
  // 10 x 10 grid of empty cells automatically generated

  // now fill the grid
  const std::vector<std::pair<char,uint>>
      boats{{'A',5}, {'C',4}, {'D',3}, {'S',3}, {'M',2}};

  // small helper clas
  struct Coord
  {
    uint row, col;
  };

  for(const auto &boat: boats)
  {

    const auto type = boat.first;
    const auto length = boat.second;

    remaining += length;

    while(true)
    {
    // assume horizontal for now

    const uint row0 = rand() % 10;
    const uint col0 = rand() % (10-length);
    std::vector<Coord> coordinates(length, {row0,col0});
    for(uint i = 0; i < length; ++i)
      coordinates[i].col = col0 + i;

    // go to vertical?
    if(rand() % 2 == 0)
    {
      for(auto &coord: coordinates)
        std::swap(coord.row, coord.col);
    }

    // check these coordinates are empty
    if(std::all_of(coordinates.begin(), coordinates.end(),
                   [&](const Coord &coord)
    {return cell(coord.row, coord.col).type == '.';}))
    {
      //  write the boat
      for(const auto &coord: coordinates)
        cell(coord.row, coord.col) = type;

      break;
    }
  }

  }
}


void Player::display()
{
  std::cout << "\n\n   1 2 3 4 5 6 7 8 9 10" << std::endl;

  for(auto row = 0; row < 10; ++row)
  {
    std::cout << row+1 << " ";
    if(row != 9)
      std::cout << " ";

    for(auto col = 0; col < 10; ++col)
      std::cout << cell(row, col).content() << " ";
    std::cout << std::endl;
  }
}

bool Player::shoot(Player & other)
{
  const uint row = rand() % 10;
  const uint col = rand() % 10;
  auto & target = other.cell(row,col);

  if(target.makeVisible())
  {
    std::cout << "You have hit a " << target.type << "!\n";
    other.remaining--;
  }

  return other.remaining == 0;
}
