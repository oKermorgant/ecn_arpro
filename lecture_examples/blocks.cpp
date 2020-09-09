#include<iostream>

using std::cout ; using std::endl ;


int main ()
{
  int i = 2;
  int k = 3;

  cout << i << endl ;  // prints  2


  if (i == 2)
  {
    int j = 3;
    int i = 4;
    cout << i << endl ; // prints 4, original is shadowed
    cout << j << endl ; // prints  3
    k = 5;
  }

  cout << i << endl ;  // prints  2
  //cout << j << endl ;  // j does  not exist , does not compile
  cout << k << endl ;  // prints  5
}
