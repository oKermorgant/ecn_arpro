#include <iostream>
#include <stdlib.h>

unsigned long int Fact(const unsigned int &n)
{
    if(n == 0 || n == 1)
        return 1;
    return n*Fact(n-1);
}

int main(int argc, char ** argv)
{

const unsigned int n = atoi(argv[1]);
std::cout << Fact(n)<< std::endl;
}
