#include <iostream>
#include <array>

using namespace std;

template <size_t n>
void printArray(const array<int, n> &arr)
{
  for(auto &v: arr)
    cout << v << " ";
  cout << endl;
}


int main()
{

 // array<int, 5> a{{1, [3]=2}};
  array<int, 5> a{0,1,4,3,2};
  printArray(a);





}
