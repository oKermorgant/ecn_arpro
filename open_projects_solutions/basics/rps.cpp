#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <array>
#include <algorithm>

struct Pick
{
  enum class Status{TIE, WINS, LOSES};

  int number; // 0 = rock, 1 = paper, 2 = scissors
  inline static const std::string choices = "RPS";

  Pick(char c = '0')  // a chosen pick
  {
    for(number = 0; number < 3; ++number)
    {
      if(c == choices[number])
        return;
    }
    // fallback to random pick
    number = rand() % 3;
    std::cout << "The computer has chosen " << choices[number] << std::endl;
  }

  static bool isValid(char c)
  {
    return choices.find(c) != choices.npos;
  }

  Status compareTo(const Pick &other) const
  {
    int diff = (number - other.number + 3) % 3;
    if(diff == 0)
      return Status::TIE;
    if(diff == 2)
      return Status::LOSES;
    return Status::WINS;
  }
};

using namespace std;

int main()
{
  while(true)
  {
    // ask for human input
    char player_choice('0');
    while(!Pick::isValid(player_choice))
    {
      cout << "Type R (Rock), P (Paper) or S (Scissors) (or Q to quit): ";
      cin >> player_choice;

      if(player_choice == 'Q')
        return 0;
    }

    // chosen pick for the player
    const Pick player_pick(player_choice);

    // random pick from the computer
    const Pick computer_pick;

    switch (player_pick.compareTo(computer_pick))
    {
    case Pick::Status::TIE:
      std::cout << "It is a tie\n";
      break;
    case Pick::Status::WINS:
      std::cout << "You win\n";
      break;
    case Pick::Status::LOSES:
      std::cout << "You lose\n";
      break;
    }
  }
}
