#include <array>
#include <ostream>
#include <algorithm>
#include <iostream>

namespace fibonacci
{

template <size_t max_digits>
struct LargeNumber
{
  std::array<int8_t, max_digits> digits{};
  LargeNumber(int n = 0)
  {
    for(size_t i = 0; i < max_digits && n; i++)
    {
      digits[i] = n%10;
      n /= 10;
    }
  }

  struct hash
  {
    size_t operator()(const LargeNumber &number) const
    {
      auto seed{max_digits};
      for(auto& i : number.digits) {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };




  LargeNumber(const LargeNumber &other) : digits{other.digits}
  {}

  inline LargeNumber operator+(const LargeNumber &other) const
  {
    LargeNumber result{other};

    for(size_t i = 0; i < max_digits; ++i)
    {
      result.digits[i] += digits[i];
      if(result.digits[i] >= 10)
      {
        result.digits[i] -= 10;
        if(i != max_digits-1)
          result.digits[i+1] += 1;
        else
          std::cerr << "digits overflow with " << *this << " + " << other << std::endl;
      }
    }
    return result;
  }

  inline bool operator==(const LargeNumber &other) const
  {
    return digits == other.digits;
  }
  inline bool operator<(const LargeNumber &other) const
  {
    for(size_t i = 0; i < max_digits; ++i)
    {
      const auto idx{max_digits-i-1};
      if(digits[idx] != other.digits[idx])
        return digits[idx] < other.digits[idx];
    }
    return false;
  }
  inline bool lessThan2() const
  {
    return std::all_of(digits.begin()+1, digits.end(), [](auto d){return d == 0;})
        && digits[0] < 2;
  }

  inline LargeNumber minusOne() const
  {
    LargeNumber minus_one{*this};

    const auto first{std::find_if(minus_one.digits.begin(),
                                  minus_one.digits.end(),
                                  [](auto d){return d != 0;})};
    if(first == minus_one.digits.end())
      return minus_one;
    (*first)--;
    for(auto prev = minus_one.digits.begin(); prev != first; ++prev)
      *prev = 9;
    return minus_one;
  }

  inline LargeNumber minusTwo() const
  {
    return minusOne().minusOne();
  }

  friend std::ostream& operator<<(std::ostream &oss, const fibonacci::LargeNumber<max_digits> &n)
  {
    const auto last{std::find_if(n.digits.rbegin(), n.digits.rend()-1,
                                 [](auto digit){return digit != 0;})};
    for(auto digit = last; digit != n.digits.rend(); ++digit)
      oss << ((int) *digit);
    return oss;
  }

};


}
