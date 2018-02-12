#include <iostream>

int main(int argc, char ** argv)
{
// conditions when I want to stop
const double error_min = 0.01;
const unsigned int iter_max = 1000;

// initialize loop variables
bool external_cancel = false;
double error = 2*error_min; // have to assign otherwise is 0
unsigned int iter(0);

while((iter < iter_max) && (error > error_min) && !external_cancel)
{
    // update iteration count
    iter++;
    
    // update error
    error = .99999*error;
    
    // check for external cancel

    std::cout << "iter: " << iter << ", Error: " << error << std::endl;

}
std::cout << "End of loop!"<< std::endl;    
}
