#include <visp/vpMatrix.h>
#include <visp/vpHomogeneousMatrix.h>
#include <iostream>

int main(int argc,char** argv)
{
  vpMatrix M(4,4);
  vpColVector v(3);

std::cout << M*v << std::endl;

M.inverseByLU() * M;

vpHomogeneousMatrix Mo;
vpRotationMatrix R;
std::cout << R.t() * R << std::endl;

}
