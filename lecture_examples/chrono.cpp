#include <iostream>
#include <vector>
#include <chrono>

using std::vector;
using std::cout;
using std::endl;

const int n = 100;
typedef std::chrono::time_point<std::chrono::system_clock> chrono;

class LargeObject
{
public:
    LargeObject()
    {
        laaarge.resize(100);
        for(auto &v: laaarge)
        {
            v.resize(100);
            for(auto &elem: v)
                elem = std::rand()%256;
        }
    }

    vector<vector<double>> laaarge;
};

void printChrono(chrono start, std::string msg)
{
    chrono end = std::chrono::system_clock::now();
    std::cout << msg << " - elapsed time: " <<
                 std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count() << " ms" << std::endl;
}

int loop_index(vector<LargeObject> &_v)
{
    auto start = std::chrono::system_clock::now();
    int r = 0;
    for(unsigned i=0; i < _v.size(); i++)
        r += _v[i].laaarge[50][50];
    printChrono(start, "index");
    return r;
}

int loop_iterator(vector<LargeObject> &_v)
{
     auto start = std::chrono::system_clock::now();
    int r = 0;
    for(vector<LargeObject>::iterator it = _v.begin(); it!=_v.end(); it++)
        r += it->laaarge[50][50];
    printChrono(start, "iterator");
    return r;
}

int loop_auto(vector<LargeObject> &_v)
{
     auto start = std::chrono::system_clock::now();
    int r = 0;
    for(auto x : _v)
        r += x.laaarge[50][50];
    printChrono(start, "auto");
    return r;
}

int loop_autoref(vector<LargeObject> &_v)
{
    auto start = std::chrono::system_clock::now();
    int r = 0;
    for(auto &x : _v)
        r += x.laaarge[50][50];
    printChrono(start, "auto&");
    return r;
}

int loop_constautoref(vector<LargeObject> &_v)
{
    auto start = std::chrono::system_clock::now();
    int r = 0;
    for(const auto &x : _v)
        r += x.laaarge[50][50];
    printChrono(start, "const auto &");
    return r;
}



int main(int argc, char ** argv)
{
    vector<LargeObject> v(100000);
cout <<  loop_autoref(v) << endl;
    cout << loop_index(v) << endl;
    cout <<  loop_auto(v) << endl;

    cout <<  loop_iterator(v) << endl;
    cout << loop_constautoref(v) << endl;

}
