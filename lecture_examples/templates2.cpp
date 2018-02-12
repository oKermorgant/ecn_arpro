#include <iostream>
#include <string>
#include <vector>

template <class T> T min(T a, T b)
{
    if(a < b)
        return a; return b;
}


int main()
{
    min(1,2);
    min(1.1,2.2);
    min<int>(1, 1.2);

    std::vector<int> a, b;
    //min(a,b);

}
