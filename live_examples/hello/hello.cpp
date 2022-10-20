#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

  vector<int> v{1,4,3,0,5};

  auto best{std::min_element(v.begin(), v.end())};

  cout << *best << " @ " << distance(v.begin(), best) << endl;

  for(int i = 0; i < 10; ++i)
    v.push_back(6);

  cout << *best << " @ " << distance(v.begin(), best) << endl;





}
