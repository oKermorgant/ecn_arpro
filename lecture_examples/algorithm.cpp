#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

void Print(string start, int i, string end = "")
{
    cout << start << i << end << endl;
}

void PrintVec(vector<int> vec)
{
    for(auto v: vec)
        cout << v << " ";
    cout << endl;
}

void PrintIndexAndValue(string s, vector<int> &vec, vector<int>::iterator &idx)
{
    cout << s << " is at " << distance(vec.begin(), idx) << " and equal to " << *idx << endl;

}
bool is_odd(int &v) {return v%2==1;}


int main()
{
    // define a vector of integers
    vector<int> vec = {1,3,4,5,0,2,1,9,10,1};

    cout << "vec is of length " << vec.size() << endl;

    // count how many 1's
    Print("There are ", count(vec.begin(),vec.end(),1), " 1's in vec");

    // count how many odd numbers
    int odds =  count_if(vec.begin(),vec.end(),
                         [](int &v) {return v%2==1;});

    Print("There are ", odds, " odd numbers in vec");

    // find the index of 9
    // actually returns a pointer to the found element

    auto idx = find(vec.begin(), vec.end(), 9);

    // get the distance from 1st element to found element
    Print("9 is at index ", distance(vec.begin(), idx), "");
    if(idx == vec.end())
        cout << " it means it was not found" << endl;

    // where is the smallest element?
    idx = std::min_element(vec.begin(), vec.end());
    PrintIndexAndValue("The smallest number", vec, idx);

    // what if the searched number is not in vec?
    idx = find(vec.begin(), vec.end(), 14);
    Print("14 is at index ", distance(vec.begin(), idx));
    if(idx == vec.end())
        cout << " it means it was not found" << endl;

    // find the index of the first even number
    idx = find_if(vec.begin(), vec.end(),
                  [](int v) {return v%2 == 0;});
    
    PrintIndexAndValue("The first even number", vec, idx);

    // sort vec according to usual sorting
    cout << endl << "Sorting vec: ";
    sort(vec.begin(), vec.end());
    // also prints the new v
    PrintVec(vec);
    // get position of the first odd number
    idx = find_if(vec.begin(), vec.end(),
                  [](int v) {return v%2 == 1;}
    );
    PrintIndexAndValue("The first odd number", vec, idx);

    // sort vec according to 3 modulus
    cout << endl << "Sorting vec with %3: ";
    sort(vec.begin(), vec.end(), [](int a, int b){return a%3 < b%3;});



    // print it
    PrintVec(vec);
    // get position of the first odd number
    idx = find_if(vec.begin(), vec.end(),
                  [](int v) {return v%2 == 1;});
    PrintIndexAndValue("The first odd number", vec, idx);

    // add 1 to all elements of vec
    cout << endl << "Adding 1: ";
    for(auto &v: vec)
        cout << ++v << " ";
    cout << endl;
    // get position of the first odd number
    idx = find_if(vec.begin(), vec.end(),
                  [](int v) {return v%2 == 1;});
    PrintIndexAndValue("The first odd number", vec, idx);


    // get the 4 smallest element at the beginning of the vector
    cout << endl << "Putting 4 smallest at the beginning (without sorting them)\n";
    std::nth_element(vec.begin(), vec.begin()+4, vec.end());
    // print it
    PrintVec(vec);

    // sort only indices from 4 to the end
    cout << endl << "Sorting only from index 4 to the end" << endl;
    sort(vec.begin()+4, vec.end());
    // print it
    PrintVec(vec);


}
