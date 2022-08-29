#include <iostream>
#include <vector>

using namespace std;

struct Dummy
{
  double value{0};
  Dummy(double value = 0.) : value{value}
  {
    cout << "  constructing Dummy(" << value << ")" << std::endl;
  }
  Dummy(const Dummy &other) : value{other.value}
  {
    cout << "  copy-constructing from Dummy(" << other.value << ")" << std::endl;
  }
  Dummy(const Dummy &&other) noexcept : value{move(other.value)}
  {
    cout << "  move-constructing from Dummy(" << other.value << ")" << std::endl;
  }
  ~Dummy()
  {
    cout << "    destructing Dummy(" << value << ")" << endl;
  }
  void print() const
  {
    cout << "    my value is " << value << endl;
  }

};

Dummy someFct(double v)
{
  Dummy d(v);
  return d;
}


int main()
{
  // will call base constructor
  Dummy d(1);

  // will call copy constructor
  auto copy = d;

  // will call base constructor in function, but no copy to output
  auto output = someFct(3.);

  cout << "Build a vector of size 3" << endl;
  // how is a vector of Dummy created?
  vector<Dummy> vec{{1.,2.,3.}};

  const auto use_reserve{false};

  if(use_reserve)
  {
    cout << "Reserving space" << endl;
    vec.reserve(8);
  }

  // resizing the vector may lead to reallocating all objects
  cout << "push_back element to the vector" << endl;
  vec.push_back(Dummy{4.});
  cout << "emplace_back element to the vector" << endl;
  vec.emplace_back(5.);
  cout << "Adding an element to the vector" << endl;
  vec.push_back(Dummy{6.});
  cout << "Adding an element to the vector" << endl;
  vec.push_back(Dummy{7.});

  // raw loop
  cout << "Raw loop" << endl;
  for(size_t i = 0; i < vec.size(); ++i)
    auto di = vec[i];

  cout << "Range-based for loop" << endl;
  for(auto di: vec)
    di.print();

  cout << "Range-based for loop, using reference" << endl;
  for(const auto &di: vec)
    di.print();

  if(true)
  {
    cout << "Inside a block" << endl;
    auto d4 = Dummy(10);
    cout << "End of block" << endl;
  }

cout << "end of program" << endl;
}
