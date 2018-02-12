#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void print(string s, int v)
{
    cout << s << ": " << v << endl;
}

int main()
{
    int i = 2, k=3;
    print("i",i);
    print("k",k);
    if(i == 2)
    {
        cout << "Entered if block" << endl;
        int j = 3;
        i = 4;
        k = 5;
        print("i",i);
        print("j",j);
        print("k",k);
    }
    cout << "Left if block" << endl;
    print("i",i);
    //print("j",j);
    print("k",k);
}
