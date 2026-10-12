

#include <iostream>
#include <algorithm>

int main()
{

  auto low{1};
  auto high{100};
  const auto secret{48};

  while(true)
  {
    const auto guess{(low+high)/2};
    std::cout << "Asking " << guess << std::endl;
    if(guess < secret)
      low = guess;
    else if(guess > secret)
      high = guess;
    else
          break;
  }








}
