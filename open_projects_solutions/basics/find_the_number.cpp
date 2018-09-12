#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

int main(int argc, char ** argv)
{
    // if no arguments, the human tries to guess
    const bool human_guess = (argc == 1);

    if(human_guess)
    {
        srand(time(0));
        //srand(100);
        const unsigned int n = (rand() % 100) + 1;
        cout << "Random number: " << n << '\n';
        unsigned int m;
        while(true)
        {
            // ask the user for a number
            cout << "Please enter a number (1-100): "; cin >> m;

            // test against n
            if(m == n)
            {
                cout << "That's it, congratulations" << endl;
                break;
            }
            else if(m < n)
                cout << "Too small" << endl;
            else
                cout << "Too large" << endl;
        }

    }
    else
    {
        unsigned int lower = 1, upper = 100;
        unsigned int guess, response;
        while(true)
        {
            guess = 0.5*(lower + upper);
            cout << "   0 if ok, 1 if too small, 2 if too large" << endl;
            cout << "Is it " << guess << "? - ";
            cin >> response;
            if(response == 0)
            {
                cout << " I knew it!" << endl;
                break;
            }
            else if(lower >= upper)
            {
                cout << "I think you are cheating" << endl;
                break;
            }
            else if(response == 1)
                lower = guess + 1;
            else
                upper = guess - 1;
        }
    }
}
