#include <player.h>
#include <iostream>
#include <algorithm>

using namespace std;

int randMax(int n)
{
  return rand() % n;
}

Player::Player()
{
  placeBoats();
}

void Player::placeBoats()
{
  cout << "Placing boats" << endl;
  // fill boats vector

  const std::map<Ship, int> fleet
  {
    {Ship::Carrier, 5},
    {Ship::Cruiser, 4},
    {Ship::Destroyer, 3},
    {Ship::Minesweeper, 3},
    {Ship::Submarine, 2}
  };

  for(auto &[ship, length]: fleet)
  {
    Boat boat{ship};

    while(true)
    {

      // init and check random coordinates
      const auto orientation{randMax(2)};
      auto row{randMax(10)};
      auto col{randMax(11-length)};
      if(orientation == 1) // vertical
        swap(row, col);

      boat.init(row, col, orientation, length);

      if(std::none_of(boats.begin(), boats.end(),
                      [boat](const auto &other)
      {return other.collides(boat);}))
      {
        boats.push_back(boat);
    cout << "Writing " << print(ship) << std::endl;
        break;
      }
    }
  }





}





void Player::display()
{
  std::array<std::array<char, 10>, 10> grid;
  for(auto& row: grid)
  {
    std::fill(row.begin(), row.end(), '.');
  }

  for(const auto &boat: boats)
  {
    const auto letter{print(boat.type)};
    for(const auto &[row, col]: boat.cells )
    {
      grid[row][col] = letter;
    }
  }

  for(const auto& row: grid)
  {
    for(auto& cell: row)
    {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}




void Player::shoot(Player other)
{

}
