#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <algorithm>


using namespace std;

int main(int argc, char ** argv)
{
    srand(time(NULL));

    vector<string> RPS = {"r", "p", "s"};
    vector<string> RPS2 = {"rock", "paper", "scissors"};

    string rps;
    int human, ai;

    while(true)
    {
        // ask for r, p or s and get index
        human = 4;
        while(human > 2)
        {
            cout << "Type r (Rock), p (Paper) or s (Scissors): ";
            cin >> rps;
            human = distance(RPS.begin(), find(RPS.begin(),RPS.end(),rps));
        }

        // random number for computer
        ai = rand() % 3;
        cout << "I went for " << RPS2[ai] << ": ";

        // compare
        ai = (human - ai + 3) % 3;
        switch(ai)
        {
        case 0:
            cout << "Draw" << endl;
            break;
        case 1:
            cout << "You win !" << endl;
            break;
        case 2:
            cout << "I win!" << endl;
            break;
        }
    }
}
