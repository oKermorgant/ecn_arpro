#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

void print(const std::unique_ptr<int> &xp)
{
  //std::cout << "ref count: " << xp.use_count() << std::endl;
  std::cout << *xp << std::endl;
}

int main()
{

  {
    auto xp = std::make_unique<int>(5);
    print(xp);
  }

  const int n = 32;

  // with base objects in the vector
  std::vector<int> v(n);
  std::generate(v.begin(), v.end(), rand);

  // location of first element of v
  auto v0 = &v[0];

  std::cout << v[0] << " = " << *v0 << std::endl;

  // they may be moved when resizing
  v.resize(n);

  std::cout << v[0] << " = " << *v0 << std::endl;


  // with pointers in the vector
  std::vector<std::unique_ptr<int>> vp;
  for(int i = 0; i < n; ++i)
    vp.push_back(std::make_unique<int>(rand()));

  // location of first element of vp
  auto vp0 = vp[0].get();

  std::cout << *vp[0] << " = " << *vp0 << std::endl;

  // the base object are not moved when resizing
  vp.resize(n+1);

  std::cout << *vp[0] << " = " << *vp0 << std::endl;

  // dangling pointer: keep the memory address of something that is not here
  int* val_ptr{};
  {
    auto val{3};
    val_ptr = &val;
  }
  std::cout << "Val is " << *val_ptr << std::endl;


}
