

// rock paper scissors

#include <iostream>
#include <map>


enum class Choice{ Paper, Rock, Scissors};

enum class Status{OK, NOPE, GONE};
enum class Connection{OK, DISCONNECT, GONE};


bool operator<(Choice c1, Choice c2)
{
  // early return / early exit
  if(c1 == Choice::Rock)
    return c2 == Choice::Paper;

  if(c1 == Choice::Paper)
    return c2 == Choice::Scissors;

  return c2 == Choice::Rock;
}

Choice getChoice()
{
  int choice;
  std::cin >> choice;
  return static_cast<Choice>(choice);
}

std::ostream  &operator<<(std::ostream  &o,
                         Choice c)
{
  switch(c)
  {
    case Choice::Rock:
      o << "Rock";
      break;
    case Choice::Paper:
      o << "Paper";
      break;
    case Choice::Scissors:
      o << "Scissors";
  }
  return o;
}




int main()
{

  auto rock{Choice::Rock};
  auto paper{Choice::Paper};

  std::cout << rock << '\n';

  std::cout << std::boolalpha << (rock < paper) << std::endl;

}
