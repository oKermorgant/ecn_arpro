#include <iostream>
#include <string>
#include <vector>

using namespace std;

int DEBUG = 0;

int getZero()
{
  return 1-1;
}

int main()
{

    if(DEBUG > 0)
        cout << " before vector init" << endl;


    std::vector<string> v(2);
    v[0] = "abc";
    v[1] = "def";    

    if(DEBUG > 1)
        cout << " before loop" << endl;

    {
        for(int i=0;i<3;++i)
            cout << v[i] << endl;
    }

    if(DEBUG > 1)
        cout << " after loop" << endl;




}
