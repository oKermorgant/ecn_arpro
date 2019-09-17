#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

int main()
{
  const int n = 32;

  // with base objects in the vector
  std::vector<int> v(n);
  std::generate(v.begin(), v.end(), rand);

  // location of first element of v
  auto v0 = &v[0];

  std::cout << v[0] << " = " << *v0 << std::endl;

  // they may be moved when resizing
  v.resize(n+1);

  std::cout << v[0] << " = " << *v0 << std::endl;


  // with pointers in the vector
  std::vector<std::unique_ptr<int>> vp;
  for(int i = 0; i < n; ++i)
    vp.push_back(std::make_unique<int>(rand()));

  // location of first element of vp
  auto vp0 = vp[0].get();

  std::cout << *vp[0].get() << " = " << *vp0 << std::endl;

  // the base object are not moved when resizing
  vp.resize(n+1);

  std::cout << *vp[0].get() << " = " << *vp0 << std::endl;

}
