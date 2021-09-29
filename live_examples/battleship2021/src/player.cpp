#include <player.h>
#include <iostream>
#include <map>
#include <random>
#include <algorithm>

using namespace std;

const auto VERTICAL{0};
const auto HORIZONTAL{1};

struct Coord{int row, col;};

std::vector<Coord> randomCandidate(int length)
{
  std::random_device device;
  static std::mt19937 generator(device());

  const auto orientation(std::uniform_int_distribution<>(0, 1)(generator));

  const auto max_row(orientation == VERTICAL ? 9-length : 9);
  const auto max_col(orientation == HORIZONTAL ? 9-length : 9);

  const auto start_row(std::uniform_int_distribution<>(0, max_row)(generator));
  const auto start_col(std::uniform_int_distribution<>(0, max_col)(generator));

  const int row_inc{orientation == HORIZONTAL ? 0 : 1};
  const int col_inc{1-row_inc};

  std::vector<Coord> cells;
  cells.reserve(length);
  for(auto step = 0; step < length; ++step)
    cells.push_back({start_row + step*row_inc, start_col + step*col_inc});

  return cells;
}



Player::Player() : grid{}
{
  placeBoats();
}

void Player::display()
{
  for(const auto &row: grid)
  {
    for(auto cell: row)
    {
      cout << cell.display() << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void Player::shoot(Player &other)
{
  other.grid[0][0].hit = true;
}

void Player::placeBoats()
{
  const std::map<Boat, int> sizes{
    {Boat::AIRCRAFT, 5},
    {Boat::MINESWEEPER, 2},
    {Boat::SUBMARINE, 3},
    {Boat::DESTROYER, 3},
    {Boat::CRUISER, 4}
  };

  for(const auto [boat, length]: sizes)
  {
    while(true)
    {
      const auto cells{randomCandidate(length)};

      if(std::any_of(cells.begin(), cells.end(), [this](auto cell)
      {return grid[cell.row][cell.col].boat != Boat::NONE;}))
        continue;

      // finally place this boat
      for(const auto &cell: cells)
        grid[cell.row][cell.col].boat = boat;

      break;
    }
  }
}











