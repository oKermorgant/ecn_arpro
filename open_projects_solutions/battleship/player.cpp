#include "player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>

using namespace std;

// static variables
// 0 = nothing
// 1 = missed
// 2 = minesweeper (length 2)
// 3 = submarine (length 3)
// 4 = destroyer (length 3)
// 5 = cruiser (length 4)
// 6 = aircraft carrier (length 5)
// negative = boat hit
std::vector<std::string> Player::legend = {".", "x", "M", "S", "D", "C", "A"};

Player::Player(std::string _name, bool _human)
{

    name = _name;
    // store if human
    human = _human;

    // we play on a 10x10 grid
    grid.resize(100,0);
    // initialize grid
    srand (clock());
    alive = {2,3,3,4,5};  // alive points per boat = lengths
    unsigned int dir, r, c;
    for(unsigned int i=0;i<alive.size();++i)
    {
        bool occupied = true;
        // try to find a place for this boat
        while(occupied)
        {
            dir = rand() % 2;   // 0 = horizontal, 1 = vertical
            r = rand() % (10*(1-dir) + (10-alive[i])*dir);  // starting row
            c = rand() % (10*(dir) + (10-alive[i])*(1-dir));  // starting column

            // test if this slot is ok
            occupied = false;
            for(unsigned int j=0;j<alive[i];++j)
            {
                if(cell(r + j*dir, c + j*(1-dir)))
                    occupied = true;
            }
        }

        // actually write the boat
        for(unsigned int j=0;j<alive[i];++j)
            cell(r + j*dir, c + j*(1-dir)) = i+2;   // boats start at 2
    }

    // no history
    hist.clear();

}

// prints this grid and the one of the other player
void Player::Print(Player &other)
{
    unsigned int i;
    // begin with the names
    cout << "      "<< name << "                        "<< other.name << endl;


    // then the column numbers
    for(unsigned int j=0;j<2;++j)
    {
        for(i=0;i<10;++i)
            cout << i << " ";
        cout << "          ";
    }
    cout << endl;

    // then print all lines
    for(i=0;i<10;++i)
        cout << PrintLine(i) << "       " << other.PrintLine(i) << endl;
    cout << endl;
}

// returns a single line
std::string Player::PrintLine(unsigned int r)
{
    std::stringstream ss;
    ss << r;

    int v;
    string leg;
    for(unsigned int c = 0;c<10;++c)
    {
        v = cell(r,c);
        if(human)   // prints the boats
        {
            if(v < 0)
                leg = legend[1];
            else
                leg = legend[v];
        }
        else
        {
            if(v < 2)               // hit boat or nothing or miss, display it
                leg = legend[abs(v)];
            else                    // non-hit boat, do not display
                leg = legend[0];
        }
        ss << " "<< leg;
    }

    return ss.str();
}

bool Player::Shoot(Player &other)
{
    unsigned int r=0, c=0;
    if(human)
    {
        cout << name  << "'s turn, give target cell as row column: ";
        cin >> r;
        cin >> c;
    }
    else
    {
        // computer never targets the same position twice. That's about it.
        while(count(hist.begin(), hist.end(),10*r+c))
        {
            r = rand() % 10;
            c = rand() % 10;
        }
        hist.push_back(10*r+c);
        cout << name << "'s turn, target (" << r << ", "<< c << ")";
    }

    int v = other.cell(r,c);
    if(v == 0)
    {
        cout << " -> Miss !" << endl;
        other.cell(r,c) = 1;
    }
    else if(v == 1)
        cout << " -> "<< name << " already shot there..." << endl;
    else if(v > 1)
    {
        if(--(other.alive[v-2]))    // remove 1 but still is non-null -> hit but not sunk
            cout << " -> "<< name << " hit a " << legend[v] << "!"<< endl;
        else
            cout << " -> "<< name << " sank a " << legend[v] << "!"<< endl;

        other.cell(r,c) *= -1;
    }

    // count if any boats left
    int total = 0;
    for(int pts: alive)
        total += pts;

    return total == 0;    // no boats left -> over
}



