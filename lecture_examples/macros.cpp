#include <iostream>

#define WITH_THIS

#define sum(a,b) (a+b)

#define true false  // we can do horrible things with #define

int main()
{


#ifdef WITH_THIS
  std::cout << "in WITH_THIS block" << std::endl;
#else
  std::cout << "WITH_THIS not defined" << std::endl;
  1+"abc";  // obvious error
#endif

  if(true)
    std::cout << "In if(true) block" << std::endl;
  else
    std::cout << "In if(false) block" << std::endl;

  std::cout << sum(3, 4) << std::endl;
  std::cout << sum(3, "ab") << std::endl;



}
