#include <visp/vpMatrix.h>


int main()
{
  vpMatrix M(4,4);
  vpColVector v(3);

  std::cout << M*v << std::endl;

}
