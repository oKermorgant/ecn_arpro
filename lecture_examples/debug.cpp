#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

int DEBUG = 0;

int main()
{

    if(DEBUG > 0)
        cout << " before vector init" << endl;


    std::vector<string> v(2);
    v[0] = "abc";
    v[1] = "def";

    if(DEBUG > 1)
        cout << " before loop" << endl;
   // try
    {
        for(int i=0;i<3;++i)
            cout << v[i] << endl;
    }
  /*  catch(...)
    {

    }*/

    if(DEBUG > 1)
        cout << " after loop" << endl;




}
