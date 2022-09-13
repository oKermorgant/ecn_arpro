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

  const int row_inc = orientation == HORIZONTAL ? 0 : 1;
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
    for(auto &cell: row)
    {
      cout << cell.display() << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void Player::shoot(Player &other)
{

  static std::default_random_engine generator;
  std::uniform_int_distribution<> random_coord(0, 9);

  auto row{random_coord(generator)};
  auto col{random_coord(generator)};

  while(other.grid[row][col].hit)
  {
    row = random_coord(generator);
    col = random_coord(generator);
  }
  //    std::cout << "targetting " << row << ", " << col << std::endl;
  other.hitCell(row, col);
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
    live_boats += length;

    while(true)
    {
      const auto cells{randomCandidate(length)};

      if(std::any_of(cells.begin(), cells.end(), [this](auto cell)
      {return at(cell.row,cell.col) != Boat::NONE;}))
        continue;

      // finally place this boat
      for(const auto &cell: cells)
        grid[cell.row][cell.col].boat = boat;

      break;
    }
  }
}

bool Player::isAlive()
{
  return live_boats;
}

void Player::hitCell(int row, int col)
{
  if(grid[row][col].hit)  return;

  grid[row][col].hit = true;

  if(grid[row][col].boat != Boat::NONE)
    live_boats--;
}
