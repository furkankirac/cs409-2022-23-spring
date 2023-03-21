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

template<typename T>
struct Value
{
    T v;
    string name;
};

template<typename T>
void printLine(const T& value) // Value<K>
{
    cout << value.v << endl;
}

void printLine(int v) // Value<K>
{
    cout << v << endl;
}


//struct IntegerValue
//{
//    int i;
//    string name;
//};

//struct FloatValue
//{
//    float f;
//    string name;
//};

//struct DoubleValue
//{
//    double d;
//    string name;
//};

int main(int argc, char* argv[])
{
//    auto v_i = IntegerValue{5, "Five"};
//    auto v_f = FloatValue{3.14f, "PI"};
//    auto v_d = DoubleValue{9.8, "G"};
    auto v_i = Value<int>{5, "Five"};
    auto v_f = Value<float>{3.14f, "PI"};
    auto v_d = Value<double>{9.8, "G"};

//    printLine<Value<int>>(v_i);
//    printLine<Value<float>>(v_f);
//    printLine<Value<double>>(v_d);

    printLine(v_i);
    printLine(v_f);
    printLine(v_d);

    printLine(500);

    return 0;
}
