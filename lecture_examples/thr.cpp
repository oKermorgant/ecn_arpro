
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string>


using namespace std;

int Count(int id, int i)
{
    std::string spaces = "";
    for(int k=0;k<30*(id-1);++k)
        spaces += " ";
    int c = 1;
    for(unsigned int k=0;k<i;++k)
    {
        c *= k+1;
        printf("%sfunction: %i, count: %i\n", spaces.c_str(), id, k);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return c;
}


int main(int argc, char ** argv)
{

    std::cout << "Without threads" << std::endl;
    Count(1, 1000);
    Count(2, 1000);

std::cout << "With threads" << std::endl;
    std::thread t1(Count, 1, 1000);
    std::thread t2(Count, 2, 1000);

    t1.join();
    t2.join();


}
