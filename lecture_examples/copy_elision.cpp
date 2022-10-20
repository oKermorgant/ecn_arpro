#include <iostream>
#include <vector>

using namespace std;

struct Dummy
{
  static uint dummies;
  uint value{0};
  bool moved_away{false};
  Dummy() : value{dummies++}
  {
    cout << "  constructing Dummy(" << value << ")" << std::endl;
  }
  Dummy(const Dummy &other) : value{other.value}
  {
    cout << "  copy-constructing from Dummy(" << other.value << ")" << std::endl;
  }
  Dummy(Dummy &&other) noexcept : value{move(other.value)}
  {
    cout << "  move-constructing from Dummy(" << other.value << ")" << std::endl;
    other.moved_away = true;
  }
  ~Dummy()
  {
    cout << "    destructing Dummy(" << value << ")";
    if(moved_away)
      cout << " / was moved away";
    cout << std::endl;
  }
  void print() const
  {
    cout << "    my value is " << value << endl;
  }

};

uint Dummy::dummies{0};

Dummy someFct()
{
  cout << "\nA function that returns a dummy\n";
  Dummy d;
  return d;
}

void detailVector(const vector<Dummy> &vec, const string &reason)
{
  cout << '\n' << reason
       << " (size = " << vec.size()
       << " / capacity = " << vec.capacity()
       << ")\n";
}


int main()
{
  // will call base constructor
  Dummy d;

  // will call copy constructor
  auto copy = d;

  // will call base constructor in function, but no copy to output
  auto output = someFct();

  cout << "\nBuild a vector of size 3" << endl;
  // how is a vector of Dummy created?
  vector<Dummy> vec(3);

  const auto use_reserve{false};

  if(use_reserve)
  {
    cout << "\nReserving space" << endl;
    vec.reserve(8);
  }

  // resizing the vector may lead to reallocating all objects
  detailVector(vec, "push_back to vector");
  vec.push_back(Dummy());
  detailVector(vec, "emplace_back to vector");
  vec.emplace_back();
  detailVector(vec, "push_back to vector");
  vec.push_back({});
  detailVector(vec, "emplace_back to vector");
  vec.emplace_back();

  cout << "\nBack to size 2" << endl;
  vec.resize(2);
  detailVector(vec, "new vector state");

  // raw loop
  cout << "\nRaw loop" << endl;
  for(size_t i = 0; i < vec.size(); ++i)
    auto di = vec[i];

  cout << "\nRange-based for loop" << endl;
  for(auto di: vec)
    di.print();

  cout << "\nRange-based for loop, using reference" << endl;
  for(const auto &di: vec)
    di.print();

  if(true)
  {
    cout << "\nInside a block" << endl;
    auto d4 = Dummy();
    cout << "End of block" << endl;
  }
  cout << "After block" << endl;

  cout << "\nend of program" << endl;
}
