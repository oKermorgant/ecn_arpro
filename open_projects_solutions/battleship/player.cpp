#include "player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>
#include <map>

using namespace std;

Player::Player(std::string _name, bool _human):
  human(_human),
  name(_name),
  boats{{'A', 5},{'C', 4},{'D', 3},{'S', 3},{'M', 2}}
{

  // initialize grid
  srand (clock());

  for(const auto &boat: boats)
  {
    const auto type = boat.first;
    const auto length = boat.second;

    uint dir(0), row(0), col(0);
    bool occupied = true;
    // try to find a place for this boat
    while(occupied)
    {
      dir = rand() % 2;   // 0 = horizontal, 1 = vertical
      row = rand() % (10*(1-dir) + (10-length)*dir);  // starting row
      col = rand() % (10*(dir) + (10-length)*(1-dir));  // starting column

      // test if this slot is ok
      occupied = false;
      for(uint j=0;j<length;++j)
      {
        if(!cell(row + j*dir, col + j*(1-dir)).isEmpty())
          occupied = true;
      }
    }

    // actually write the boat
    for(uint j=0;j<length;++j)
      cell(row + j*dir, col + j*(1-dir)) = Cell(type);   // boats start at 2
  }

  // no history
  hist.clear();

}

// prints this grid and the one of the other player
void Player::Print(const Player &other)
{
  unsigned int row;
  // begin with the names
  cout << "      "<< name << "                        "<< other.name << endl;


  // then the column numbers
  for(unsigned int j=0;j<2;++j)
  {
    for(row=0;row<10;++row)
      cout << row << " ";
    cout << "          ";
  }
  cout << endl;

  // then print all lines
  for(row=0;row<10;++row)
    cout << PrintRow(row) << "       " << other.PrintRow(row) << endl;
  cout << endl;
}

// returns a single line
std::string Player::PrintRow(uint row) const
{
  std::stringstream ss;
  ss << row;

  for(uint col = 0;col<10;++col)
    ss << " " << cell(row, col).display(human);

  return ss.str();
}

bool Player::Shoot(Player &other)
{
  unsigned int row=0, col=0;
  if(human)
  {
    cout << name  << "'s turn, give target cell as row column: ";
    cin >> row;
    cin >> col;
  }
  else
  {
    // computer never targets the same position twice. That's about it.
    while(count(hist.begin(), hist.end(),10*row+col))
    {
      row = rand() % 10;
      col = rand() % 10;
    }
    hist.push_back(10*row+col);
    cout << name << "'s turn, target (" << row << ", "<< col << ")";
  }

  auto &c = other.cell(row,col);
  if(c.type == '.')
  {
    if(c.was_hit)
      cout << " -> "<< name << " already shot there..." << endl;
    else
    {
      cout << " -> Miss !" << endl;
    }

  }
  else
  {
  if(--(other.boats[c.type])) // remove 1 but still is non-null -> hit but not sunk
    cout << " -> "<< name << " hit a " << c.type << "!"<< endl;
  else
    cout << " -> "<< name << " sank a " << c.type << "!"<< endl;
  }
  c.was_hit = true;

  // count if any boats left

  int total = 0;
  for(const auto &boat: other.boats)
    total += boat.second;

  return total == 0;    // no boats left -> over
}



