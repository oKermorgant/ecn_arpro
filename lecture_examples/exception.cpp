#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// an exception for matrix multiplication


class Matrix
{
public:
    Matrix(int r, int c)
    {
        rows = r;
        cols = c;
        data.resize(r, vector<double>(c, 0));
    }
    double& operator()(int r, int c)
    {
        if(r < rows && c < cols)
            return data[r][c];
        stringstream ss;
        ss << "Bad index for " << rows << "x" << cols << " matrix";
              ss << ": (" << r << "," << c << ")";
        throw ss.str();;
    }

    void print() const
    {
        for(auto &row: data)
        {
            for(auto& val: row)
                cout << val << "  ";
            cout << endl;
        }
    }

private:
    vector<vector<double>> data;
    int rows, cols;
};


int main()
{

    Matrix M(2,3);
    M.print();

    try
    {
    M(0,1) = 2;
    M.print();
    M(2,4);
}
    catch(string e)
    {
      cout << e << endl;
    }


}
