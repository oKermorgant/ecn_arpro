#include <iostream>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	// get the name of the polygon
unsigned int sides = 3;
if(argc > 1)
    sides = atoi(argv[1]);

std::string msg = "";
switch(sides)
{
    case 0:
    case 1:
    case 2:
        // do nothing
        break;
    case 3:
        msg = "This is a triangle";
        break;
    case 4:
        msg = "This is a square";
        break;
    default:
        msg = "This is too much complicated";
}
if(msg != "")
    std::cout << msg << std::endl;
else
    std::cout << "This is not a polygon"<< std::endl;
}
