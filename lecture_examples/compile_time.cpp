#include <iostream>
#include <array>
#include <vector>
#include <numeric>

struct Matrix
{
private:
  std::vector<int> data;
  uint rows, cols;


public:
  Matrix(const uint r, const uint c, int value = 0) : rows(r), cols(c), data(r*c, value) {}

  inline auto & operator()(const uint i, const uint j)
  { return data[i*cols+j];
  }
  inline auto operator()(const uint i, const uint j) const
  { return data[i*cols+j];
  }

  inline Matrix operator*(const Matrix &M)
  {
    Matrix out(rows, M.cols);
    for (uint i = 0; i < rows; ++i)
      for (uint j = 0; j < M.cols; ++j)
        for (uint k = 0; k < cols; ++k)
          out(i,j) += this->operator()(i,k) * M(k,j);

    return out;
  }


};


int main()
{

  // print a litteral
  std::cout << 45 << std::endl;

  // print a simple computation
  const auto n1{5};
  const auto n2{9};
  std::cout << n1 * n2 << std::endl;


  // print the sum of an array
  std::array<int, 9> arr;
  std::iota(arr.begin(), arr.end(), 1);
  std::cout << std::accumulate(arr.begin(), arr.end(), 0) << std::endl;

  // print the product of two matrices
  Matrix A(1,2);
  A(0,0) = 5;
  A(0,1) = 3;
  Matrix B(2,1);
  B(0,0) = 6;
  B(1,0) = 5;
  const auto C{A * B};
  std::cout << C(0,0) << std::endl;
}
