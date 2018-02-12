#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

// some animals

struct Duck {
    void quacks() {}
    string name = "duck";

};


struct Dog  {
    void barks() {}
    string name = "dog";
};


// a seagull that knows how to quack
struct SmartSeagull {
    void quacks() {}
    string name = "seagull";
};

// a square with 4 sides
struct Square {
    int sides = 4;
    string name = "square";
};

// this template function needs the argument to have a quacks() method
template <class T>
void CompileIfDuck(T animal)
{
    animal.quacks();
}

// this template function needs the argument to have a name member
template <class T>
void WhatAreYou(T object)
{
    cout << "I am a " << object.name << endl;
}




int main() {
  Duck duck;  Dog dog; SmartSeagull seagull;

  CompileIfDuck(duck);		// compiles
  //CompileIfDuck(dog);		// does not compile
  CompileIfDuck(seagull);	// compiles because the SmartSeagull struct has a quacks() method


  Square sq;
  WhatAreYou(dog);
  WhatAreYou(sq);           // compiles, does not care if argument is an animal or anything particular
  //WhatAreYou(1);          // does not compile, 1 is a int and has no member called name

}
