// implement a find the number game between 1 and 100
#include <iostream>
#include <random>

using std::cout, std::cin;

struct Point
{
  int x,y;
};

int main()
{
  // TODO use a random secret
  //std::random_device dev;
  std::default_random_engine engine(time(0));
  std::uniform_int_distribution range(1,100);
  const auto secret{range(engine)};

  auto guess{0};

  while(secret != guess)
  {
    // TODO ask for the guess
    cout << "Enter your guess: ";
    std::cin >> guess;

    // TODO check difference
    if(guess < secret)
      cout << "Too low\n";
    else if(guess > secret)
      cout << "Too high\n";
  }

 cout << "You found it!\n";




}
