#include <iostream>

// core language definitions:
// - l-value / r-value
// - chain assignment
// - constness: east/west const, pointers and const
// using / namespaces

// OOP:
// inheritance
// dynamic polymorphism / virtual functions vs RTTI
// move-ctor, move-assignment

// functional programming:
// - overloading
//   (all the operators are implemented as functions and they also can ve overloaded)

// Generics / Templates:
// function, class, variable, type templates

#include <iostream>
#include <string>

using namespace std;

//struct string {
//    // ....
//    string() { }
//    string(const char*) { } // conversion ctor
//    string(const string&) { }
//    // ....
//};


//int foo(std::string& s) // l-value ref

void bar(const string& s)
{

}

int foo(const string& s) // l-value or r-value ref (because of constness)
{
    bar(s);
    cout << s << endl;
    return 5;
}

void print(int& k)
{
    cout << k << endl;
}

int main(int argc, char* argv[])
{
    int a, b, c; //c style variable definition; it allows uninitialized variables
    a = b = c = 5; // assignment operator runs from right to left
    // a, b and c are 5

    print(a = b = c = 50); // prints 50

    // - constness: east/west const, pointers and const

    double PI = 3.14; // east-const: double is readonly (value which is double is readonly)
    double G = 9.8;

//    double const * const PIptr = &PI; // east const
    const double * const PIptr = &PI; // west const - east const mixed. only the first const can be written at left

//    PIptr = &G; // trying to change the memory address stored in this pointer is not allowed (double * const)
//    *PIptr = G;

    cout << "address of PI = " << &PI << endl;
    cout << "stored value in PIptr = " << PIptr << endl;
    cout << "stored value in the memory being pointed by PIptr = " << *PIptr << endl;

    cout << sizeof(PI) << endl;




    // l-value ---> left value
    // r->value --> right value

//    auto a = 5;   // a --> l-value;    5 --> r-value

    foo( "Hi there" ); // const char[9] --> const char * ---> std::string
    5;

    return 0;
}
