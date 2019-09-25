#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;
using std::cout;
using std::endl;

void init(vector<int> &_v)
{
    for(unsigned int i=0;i<_v.size();++i)
        _v[i] = std::rand()%256 - 128;
}

int loop_index(vector<int> &_v)
{
    int r = 0;
    for(unsigned i=0; i < _v.size(); i++)
        r += _v[i];
    return r;
}

int loop_iterator(vector<int> &_v)
{
    int r = 0;
    for(vector<int>::iterator it = _v.begin(); it!=_v.end(); it++)
        r += *it;
    return r;
}

int loop_auto(vector<int> &_v)
{
    int r = 0;
    for(auto x : _v)
        r += x;
    return r;
}

int loop_autoref(vector<int> &_v)
{
    int r = 0;
    for(auto &x : _v)
       r += x;
    return r;
}

int loop_constautoref(vector<int> &_v)
{
    int r = 0;
    for(const auto &x : _v)
        r += x;
return r;
}

int loop_std(vector<int> & _v)
{
  return std::accumulate(_v.begin(), _v.end(), 0);
}



int main(int argc, char ** argv)
{
    vector<int> v(10000000);
    init(v);

    cout << loop_index(v) << endl;
    cout <<  loop_auto(v) << endl;
    cout <<  loop_autoref(v) << endl;
    cout <<  loop_iterator(v) << endl;
     cout << loop_constautoref(v) << endl;
    cout << loop_std(v) << endl;

    return 0;
}
