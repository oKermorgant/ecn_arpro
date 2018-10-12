#include <iostream>
#include <vector>

using namespace std;

// an exception for matrix multiplication



    virtual const char* what() const throw()
    {
        return "Division par zero";
    }


class Matrix
{
public:
    Matrix(int r, int c)
    {
        row = r;
        col = c;
        data.resize(r);
        for(auto &v: data)
            v.resize(c, 0);
    }
    double& operator()(int r, int c)
    {
        if(r < row && c < col)
            return data[r][c];
        throw string("Mauvais indices");
    }

    void print()
    {
        for(auto row: data)
        {
            for(auto val: row)
                cout << val << "  ";
            cout << endl;
        }
    }

private:
    vector<vector<double>> data;
    int row, col;
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
