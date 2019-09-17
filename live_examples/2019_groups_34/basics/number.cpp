// name of the file = number.cpp
#include <iostream>
#include <vector>
int main()
{
  srand(time(nullptr));
  const int secret  = rand() % 100 + 1;

  std::cout << "Number to be guessed is "
            << secret << std::endl;

  int guess(0);

  while(guess != secret)
  {
    // ask for number
    std::cout << "Your guess: ";
    std::cin >> guess;

    // check if lower
    if(guess < secret)
      std::cout << "Too low" << std::endl;

    // check if greater
    else if(guess > secret)
      std::cout << "Too high" << std::endl;

  }

  std::cout << "You won!" << std::endl;
}
