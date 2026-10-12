

#include <iostream>
#include <limits>
#include <random>

namespace
{
constexpr int minimum_number = 1;
constexpr int maximum_number = 100;

int read_guess()
{
  int guess{};

  while (true)
  {
    std::cout << "Enter a number (" << minimum_number << "-" << maximum_number << "): ";

    if (std::cin >> guess && guess >= minimum_number && guess <= maximum_number)
    {
      return guess;
    }

    if (std::cin.eof())
    {
      return minimum_number;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a whole number in the valid range.\n";
  }
}

bool play_round(std::mt19937& generator)
{
  std::uniform_int_distribution distribution(minimum_number, maximum_number);
  const int secret = distribution(generator);
  int attempts = 0;

  std::cout << "\nI have chosen a number between " << minimum_number << " and "
        << maximum_number << ".\n";

  while (true)
  {
    const int guess = read_guess();

    if (std::cin.eof())
    {
      return false;
    }

    ++attempts;

    if (guess < secret)
    {
      std::cout << "Too low.\n";
    }
    else if (guess > secret)
    {
      std::cout << "Too high.\n";
    }
    else
    {
      std::cout << "Correct! You found it in " << attempts << " attempt"
            << (attempts == 1 ? "" : "s") << ".\n";
      return true;
    }
  }
}

bool wants_to_play_again()
{
  char answer{};
  std::cout << "Play again? [y/N]: ";
  std::cin >> answer;
  return !std::cin.eof() && (answer == 'y' || answer == 'Y');
}
} // namespace

int main()
{
  std::random_device random_device;
  std::mt19937 generator(random_device());

  std::cout << "Find the Number\n" ;



  int b;
  std::cout << "Entrer un nombre: ";
  std::cin >> b;


    return 0;
}
