#include <vector>
#include <iostream>
#include <time.h>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;


const unsigned int SP = 2;
const unsigned int NB = 10;

void display(const vector<vector<int> > &rods)
{
    string sp = "";
    for(int i=0;i<SP;++i)
        sp += " ";

    string line;

    for(int i=NB;i != 0;--i)
    {
        for(const auto &rod: rods)
        {
            cout << sp;
            int length = 0;
            if(rod.size() < i)
                line = "|";
            else
            {
                line = "#";
                length = rod[i-1];
            }

            for(int j=0;j<NB;++j)
            {
                if(j < length)
                    line = "#" + line + "#";
                else
                    line = " " + line + " ";
            }
            cout << line;
        }
        cout << endl;
    }
    cout << endl;
}

void move_disk(const unsigned int &d, const unsigned int &a, vector<vector<int> > &rods)
{
    cout << d << " -> " << a << endl;
    bool can_move = true;
    if(rods[d].size() == 0)
        can_move = false;
    else if(rods[a].size() != 0)
    {
        if(rods[a][rods[a].size()-1] < rods[d][rods[d].size()-1])
            can_move = false;
    }

    if(can_move)
    {
        rods[a].push_back(rods[d][rods[d].size()-1]);
        rods[d].pop_back();
    }

    display(rods);

}

void put_on(const unsigned int n, const unsigned int a, vector<vector<int> > &rods)
{
    if(n == 0)
        return;

    // find P_n
    int d;
    for(d = 0;d<3;++d)
    {
        if(count(rods[d].begin(),rods[d].end(),n))
            break;
    }

    if(d == a)  // already ok
        put_on(n-1,a,rods);
    else
    {
        put_on(n-1,3-a-d,rods);
        move_disk(d, a, rods);
        put_on(n-1,a,rods);
    }
}



int main()
{
    vector<vector<int> > rods(3);
    srand(time(NULL));

    // 10 disks placed at random
    for(unsigned int i=0;i<NB;++i)
    {
        int rod = rand()%3;
        rods[rod].push_back(NB-i);
    }
    display(rods);

    // place everything on the first rod
    put_on(NB,0,rods);
}
