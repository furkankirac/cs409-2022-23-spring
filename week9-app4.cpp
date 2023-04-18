// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors
// Array<T, sz> implementation with deduction guides

#include <iostream>
#include <string>

using namespace std;


template<typename T>
void foo(T t)
{
}


#include <string>

template<typename T, size_t sz>
struct Array
{
    T values[sz];
};

Array(const char*) -> Array<string, 1>;

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors



struct Array_int_5
{
    int values[5];
};


#include <array>

template<typename ...>
struct Debugger;

int main()
{
    foo(5);  // T is deduced as int automatically
    foo("hi");  // T is deduced as const char[3] automatically

    auto array = Array<int, 5>{10, 20, 30, 40, 50};

    auto array_1string = Array{"Hi"};

//    auto t = Debugger< decltype( array_1string.values ) >{};


//    auto array2 = std::array<int, 5>{10, 20, 30, 40, 50};

    for(int i=0; i<5; i++)
        cout << array.values[i] << endl;

    return 0;
}
