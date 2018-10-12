#include <iostream>
#include <string>
#include <vector>

template <class T, class V> T min(T a, V b)
{
    if(a < b)
        return a; return b;
}


int main()
{
    min(1,2);
    min(1.1,2.2);
    std::cout << min<double, double>(2, 1.2);

   std::vector<int> a, b;
   min(a,b);

}
