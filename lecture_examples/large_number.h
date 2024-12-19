#include <ostream>
#include <algorithm>
#include <vector>




class LargeNumber
{
  std::string digits{};
  bool positive{};

  inline LargeNumber(const std::string &digits, bool positive)
    : digits{digits}, positive{positive || isNull()} {}

  inline auto simplify()
  {
    auto n{len()-1};
    while(n && !digits[n])
    {
      digits.pop_back();
      n--;
    }
    if(isNull())
      positive = true;
    return *this;
  }

  inline size_t len() const {return digits.size();}

public:

  LargeNumber(long long n = 0) : positive{n>=0}
  {
    if(!positive) n *= -1;
    do{
      digits.push_back(n % 10);
      n /= 10;
    } while (n);
  }
  LargeNumber(const LargeNumber &src) = default;

  inline char operator[](size_t i) const
  {
    return i < len() ? digits[i] : 0;
  }

  inline bool isNull() const {return digits.size() == 1 && digits[0] == 0;}
  struct hash
  {
    inline size_t operator()(const LargeNumber &number) const
    {
      return std::hash<std::string>()(number.digits);
    }
  };

  // difficult ones

  inline LargeNumber operator+(const LargeNumber &other) const
  {
    if(!positive)
      return other - (-*this);
    if(!other.positive)
      return *this - (-other);

    LargeNumber result{*this};
    const auto m{other.len()};
    auto n{len()};
    if(m > n)
      result.digits.append(m-n,0);
    n = result.len();
    char t{};
    for(size_t i = 0; i < n; ++i)
    {
      const auto s = result.digits[i] + t + other[i];
      t = s / 10;
      result.digits[i] = (s % 10);
    }
    if(t)
      result.digits.push_back(t);
    return result;
  }

  inline bool operator<(const LargeNumber &other) const
  {    
    if(positive && !other.positive)
      return false;
    if(!positive && other.positive)
      return true;

    auto d = len();
    if(d != other.len())
      return d < other.len() == positive;

    while(d--)
    {
      if(digits[d] != other.digits[d])
        return digits[d] < other.digits[d] == positive;
    }
    return !positive;
  }

  inline LargeNumber operator-(const LargeNumber &other) const
  {
    if(*this < other)
      return -(other-*this);
    if(!positive)
      return -*this - other;
    if(!other.positive)
      return *this + (-other);

    auto n{len()};
    const auto m{other.len()};

    auto result{*this};
    int t{0};
    for(size_t i = 0; i < n; ++i)
    {
      auto s = result.digits[i] + t - other[i];
      if(s < 0)
      {
        t = -1;
        s += 10;        
      }
      else
      {
        t = 0;
      }
      result.digits[i] = s;
    }
    return result.simplify();
  }

  inline auto operator*(const LargeNumber &other) const
  {
    if(isNull() || other.isNull())
      return LargeNumber(0);

    auto n{len()};
    const auto m{other.len()};
    std::vector<char> prod(n+m, 0);
    for (size_t i = 0; i < n;i++)
    {
      for (size_t j = 0; j < m;j++)
        prod[i + j] += (digits[i] ) * (other.digits[j]);
    }
    n += m;

    auto result{*this};
    result.digits.resize(prod.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
      s = t + prod[i];
      prod[i] = s % 10;
      t = s / 10;
      result.digits[i] = prod[i];
    }
    result.positive = result.positive == other.positive;
    return result.simplify();
  }


  // easy ones

  inline LargeNumber operator-() const
  {
    return {digits, !positive};
  }

  inline auto operator==(const LargeNumber &other) const
  {
    if(digits != other.digits)
      return false;
    return positive == other.positive || isNull();
  }

  inline auto& operator+=(const LargeNumber &other)
  {
    return *this = *this + other;
  }

  inline auto& operator-=(const LargeNumber &other)
  {
    return *this = *this - other;
  }

  inline auto& operator*=(const LargeNumber &other)
  {
    return *this = *this * other;
  }

  friend auto& operator<<(std::ostream &oss, const LargeNumber &n)
  {
    if(n < 0)
      oss << '-';
    for(int d = n.len()-1; d >= 0; --d)
      oss << static_cast<short>(n.digits[d]);
    return oss;
  }
};


inline auto operator+(ulong n, const LargeNumber &l)
{
  return l + n;
}
inline auto operator-(ulong n, const LargeNumber &l)
{
  return l - n;
}
inline auto operator*(ulong n, const LargeNumber &l)
{
  return l * n;
}
