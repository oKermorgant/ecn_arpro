#include <iostream>
#include <cstdlib>


int main()
{
  srand(time(nullptr));

  const int secret = rand() % 100 + 1;
  std::cout << "(i have generated " << secret << ")" << std::endl;

  int guess = 0;

  while(guess != secret)
  {
    std::cout << "Input a number between 1 and 100: ";
    std::cin >> guess;

    if(guess < secret)
      std::cout << "Too small" << std::endl;
    else if(guess > secret)
      std::cout << "Too large" << std::endl;
  }

  std::cout << "You have won!" << std::endl;


}
