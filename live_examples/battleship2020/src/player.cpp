#include <player.h>
#include <iostream>
#include <algorithm>

int randint(int max)
{
  return rand() % max;
}

std::vector<Boat*> Player::randomPlacement(int length)
{
  std::vector<Boat*> boats;

  const bool vertical(randint(2));
  int row(randint(vertical ? 10-length : 10));
  int col(randint(vertical ? 10 : 10-length));

  for(int step = 0; step < length; ++step)
  {
    boats.push_back(&grid[row][col]);
    if(vertical)
      row++;
    else
      col++;
  }
  return boats;
}


Player::Player(bool human) : is_human(human)
{
  for(const auto &[type, length]: Boat::allBoats())
  {
    auto candidate_cells = randomPlacement(length);

    while(std::any_of(candidate_cells.begin(), candidate_cells.end(), [](auto boat)
    {return boat->type != BoatType::NONE;}))
    {
      candidate_cells = randomPlacement(length);
    }

    live_boats += length;
    for(auto boat: candidate_cells)
      boat->type = type;
  }
}

void Player::display(const Player &other)
{
  const std::string sep("   ");
  std::cout << std::endl;
  // column numbers on top of both grids
  for(int player = 0; player < 2; player++)
  {
    std::cout << "  ";
    for(int col = 0; col < 10; col++)
      std::cout << col << " ";
  }
  std::cout << std::endl;

  // player grid on the left, computer grid on the right
  for(int line = 0; line < 10; ++line)
  {
    std::cout << line << " ";
    displayLine(line);
    std::cout << "  ";
    other.displayLine(line);
    std::cout << line << std::endl;
  }
}

void Player::shoot(Player &other)
{
  int row(-1), col(-1);
  if(is_human)
  {

    display(other);
    while(row < 0 || row > 9 || col < 0 || col > 9)
    {
      std::cout << "Enter the coordinates as row col: ";
      std::cin >> row >> col;
    }
  }
  else
  {
    // just shoot randomly, not at an already shot boat
    row = randint(10);
    col = randint(10);
    while(other.grid[row][col].hit)
    {
      row = randint(10);
      col = randint(10);
    }
    std::cout << "I play " << row << " " << col << std::endl;
  }

  other.registerShot(row, col);
}


void Player::registerShot(int row, int col)
{
  auto &target(grid[row][col]);
  if(target.hit == false)
  {
    target.hit = true;
    if(target.type != BoatType::NONE)
    {
      live_boats--;
      std::cout << "  -> Hit a " << target.display(true) << std::endl;
    }
    else
      std::cout << "  -> That's a miss" << std::endl;
  }
  else
  {
    std::cout << "  -> already shot there..." << std::endl;
  }
}

void Player::displayLine(int line) const
{
  for(const auto &boat: grid[line])
  {
    std::cout << boat.display(!is_human) << " ";
  }
}
