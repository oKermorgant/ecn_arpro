#include <memory>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>




class Obj
{
public:

    static int created;
    static int destructed;
    int value;

    Obj(int n) : value(n%100)
    {
        created++;
    }
    ~Obj()
    {
        destructed++;
    }
};

int Obj::created = 0;
int Obj::destructed = 0;

template <class T>
void printCount(const T &v, std::string msg)
{
    std::cout << msg << std::endl;
    std::cout << "  Created: " << Obj::created << std::endl;
    std::cout << "  Destructed: " << Obj::destructed << std::endl;
    std::cout << "  In vector: " << v.size() << std::endl << std::endl;
}


void use_raw()
{
    Obj::created = Obj::destructed = 0;

    std::vector<Obj*> v;

    for(int i = 0; i < 100; ++i)
    {
        auto o = new Obj(std::rand());
        if(o->value < 10)
            v.push_back(o);
    }
    printCount(v, "Using raw pointers");
}

void use_unique()
{
    Obj::created = Obj::destructed = 0;

    std::vector<std::unique_ptr<Obj>> v;

    for(int i = 0; i < 100; ++i)
    {
        auto o = std::make_unique<Obj>(std::rand());
        if(o->value < 10)
            v.push_back(std::move(o));
    }
    printCount(v, "Using unique pointers");
}


void use_shared()
{
    Obj::created = Obj::destructed = 0;

    std::vector<std::shared_ptr<Obj>> v;

    for(int i = 0; i < 100; ++i)
    {
        auto o = std::make_shared<Obj>(std::rand());
        if(o->value < 10)
            v.push_back(o);
        std::cout << "  use counts inside loop: " << o.use_count() << std::endl;
    }
    printCount(v, "Using shared pointers");
}


int main()
{
    std::srand(time(0));
   //use_raw();
   use_unique();
  //use_shared();
}
