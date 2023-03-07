#include <iostream>

// core language definitions:
// - l-value / r-value
// - chain assignment
// - constness: east/west const, pointers and const
// using / namespaces

// OOP:
// inheritance
// dynamic polymorphism / virtual functions vs RTTI

// move-ctor, move-assignment (delayed)

// functional programming:
// - overloading
//   (all the operators are implemented as functions and they also can ve overloaded)

// Generics / Templates:
// function, class, variable, type templates

#include <iostream>
#include <string>

using namespace std;

namespace Util
{
int A = 100;
}


struct Animal // creating its own namespace called Animal
{
    string name; // 32 byte consuming thing
    Animal(const string& name = "") : name(name) { } // binds l-values and r-values

    virtual void whoAmI() { // #index 0
        cout << "Arbitrary Animal with name '" << name << "'" << endl;
    }
};

// Animal's vtable there will be only 1 virtual function: Animal::whoAmI

struct Dog : Animal
{
    string familyName;
//    using Animal::Animal;

    Dog(const string& name = "", const string& familyName = "") : Animal(name), familyName(familyName) { } // binds l-values and r-values

    void whoAmI() override { // override'ing: exact signature method is already available, we override it
        cout << "Dog with name '" << name << "'. My family is '" << familyName << "'" << endl;
    }
};

struct Shark : Animal
{
    using Animal::Animal;

    void whoAmI() override { // override'ing: exact signature method is already available, we override it
        cout << "Shark with name '" << name << "'" << endl;
    }
};


int main(int argc, char* argv[])
{
//    using Util::A;
//    cout << A << endl;

    auto a = Animal{"Poppy"};
    cout << sizeof(a) << endl;
//    a.whoAmI();

    auto d = Dog{"Poppy", "Adams"};
//    d.whoAmI();

    auto s = Shark{"Cuty"};
//    s.whoAmI();

    using AnimalPtr = Animal*;
    AnimalPtr animals[] = {&a, &d, &s, &s, &d};
    // at compile time, I created this array, I know it contains 4 items

    const auto numItems = sizeof(animals) / sizeof(AnimalPtr);
    for(int i=0; i<numItems; i++) {
//        (*animals[i]).whoAmI();
        animals[i]->whoAmI();
    }

    return 0;
}
