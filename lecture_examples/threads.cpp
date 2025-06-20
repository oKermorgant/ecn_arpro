
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string>
#include <mutex>


using namespace std;

void print(const std::string &s)
{
  static std::mutex mtx;
  mtx.lock();
  std::cout << s << std::endl;
  mtx.unlock();
}





void Count(int id, int i)
{
  std::string spaces = "";
  for(int k=0;k<30*(id-1);++k)
    spaces += " ";
  for(int k=0;k<i;++k)
  {
    print(spaces + "function: " + std::to_string(id) + ", count: " + std::to_string(k));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}


int main(int argc, char ** argv)
{
  std::cout << "Without threads" << std::endl;
 // Count(1, 10);
 // Count(2, 10);



  std::cout << "With threads" << std::endl;
  std::thread t1(Count, 1, 10);
  std::thread t2(Count, 2, 13);

  std::cout << "Waiting for t1 to end" << std::endl;
  t1.join();
  std::cout << "Waiting for t2 to end" << std::endl;
  t2.join();


}
