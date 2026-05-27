#include <iostream>

int main()
{

  auto low{1}, high{100};

  while(true)
  {
    const auto guess{(low+high)/2};

    std::cout << "\nIs it " << guess << "? [+/-/=] ";
    std::string answer;
    std::cin >> answer;

    if(answer == "=")
    {
      std::cout << "found it\n";
      break;
    }

    if(low >= high)
    {
      std::cout << "bye\n";
      break;
    }

    if(answer == "-")
      high = guess-1;
    else
      low = guess+1;
  }




}

