
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string>


using namespace std;

bool print_ok;

void Count(int id, int i)
{
    std::string spaces = "";
    for(int k=0;k<30*(id-1);++k)
        spaces += " ";
    for(unsigned int k=0;k<i;++k)
    {
        while(!print_ok)
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        print_ok = false;
        std::cout << spaces << "function: " << id << ", count: " << k << std::endl;
        print_ok = true;
        //printf("%sfunction: %i, count: %i\n", spaces.c_str(), id, k);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

}


int main(int argc, char ** argv)
{
    print_ok = true;
    std::cout << "Without threads" << std::endl;
    Count(1, 10);
    Count(2, 10);

    print_ok = true;
    std::cout << "With threads" << std::endl;
    std::thread t1(Count, 1, 10);
    std::thread t2(Count, 2, 10);

    t1.join();
    t2.join();


}
