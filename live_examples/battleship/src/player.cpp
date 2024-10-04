#include <player.h>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int randMax(int n)
{
  return rand() % n;
}

Player::Player()
{


  const vector<pair<Boat,int>> fleet{
    {Boat::Carrier, 5},
    {Boat::Submarine, 2},
    {Boat::Cruiser, 4},
    {Boat::Minesweeper, 3},
    {Boat::Destroyer, 3}
  };


  for(auto &[boat, length]: fleet)
  {

    bool empty{false};
    int row, col, orientation;

    while(not empty)
    {
      // generate random coord
      orientation = randMax(2);
      row = randMax(10);
      col = randMax(11 - length);

      if(orientation == 1)  // vertical
      {
        std::swap(row, col);
      }

      // check
      empty = true;
      for(int _ = 0; _ < length; ++_)
      {
        if(grid[row][col].boat != Boat::None)
          empty = false;
        if(orientation == 0)
          col++;
        else
          row++;
      }
      if(orientation == 0)
        col -= length;
      else
        row -= length;

    }

    // write the boat
    for(int _ = 0; _ < length; ++_)
    {
      grid[row][col].boat = boat;
      if(orientation == 0)
        col++;
      else
        row++;
    }

    //grid[row][col]




  }
}





void Player::display()
{
  for(const auto& row: grid)
  {
    for(const auto& cell: row)
    {
      cout << cell.print() << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void Player::target(Player other)
{

}












