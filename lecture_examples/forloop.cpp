#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{

// all combinations of 2 ints from 0 to 100
unsigned int i;
for(i=0; i < 99; i++)
{
    for(unsigned int j=i+1; j < 100; j++)
        std::cout << i << " and " << j << std::endl;
}       

std::vector<int> vec(6);


for(int i=0;i<6;++i)
    vec[i] = i;

for(int i=0;i<6;++i)
{
    std::cout << vec[i] << " ";
}
std::cout << '\n';




for(auto &x : vec)
{
    x = 4;
}

for(int i=0;i<6;++i)
{
    std::cout << vec[i] << " ";
}

std::cout << '\n';


for(auto x : vec)
{
    x = 5;
}

for(int i=0;i<6;++i)
{
    std::cout << vec[i] << " ";
}
std::cout << '\n';


for(auto const &x: vec)
{
   // x = 5;
    std::cout << x << " ";
}
std::cout << '\n';






/*
// this is a seg fault
std::vector<std::string> v(2);
v[0] = "Hello";
v[1] = "world";

for(int i=0;i<5;++i)
{
    std::string current = v[i];
    std::cout << current << std::endl;

}


*/
















}
