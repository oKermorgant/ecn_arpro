#include <map>
#include <vector>
#include <set>

enum class Ship
{
  Carrier,
  Submarine,
  Destroyer,
  Cruiser,
  Minesweeper
};

inline char print(Ship ship)
{
  switch(ship)
  {
    case Ship::Carrier:
      return 'A';
    case Ship::Cruiser:
      return 'C';
    case Ship::Destroyer:
      return 'D';
    case Ship::Minesweeper:
      return 'M';
    case Ship::Submarine:
      return 'S';
  }
  return {};
}

struct Coord
{
  int row, col;
  bool operator==(Coord other)
  {
    return row == other.row and col == other.col;
  }
};

class Boat
{
public:
  Ship type;
  std::vector<Coord> cells;

  void init(int row, int col, bool vertical, int length)
  {
    cells.clear();
    cells.reserve(length);
    for(int i = 0; i < length; ++i)
    {
      cells.push_back({row,col});
      if(vertical)
        row++;
      else
        col++;
    }
  }

  bool collides(const Boat &other) const
  {



    return false;
  }
};
