#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class ExamClass
{
public:
    void Print() {cout << "non-static\n";}
    static void PrintSt() {cout << "static\n";}

};


int main(int argc, char ** argv)
{
    ExamClass::PrintSt();
    ExamClass e;
    e.Print();





    std::cout << "Hello world!" << std::endl;

    std::cout << "You have " << argc << " arguments:" << endl;
    for(unsigned int i=0;i<argc;++i)
        std::cout << "  - " << argv[i] << endl;



}
