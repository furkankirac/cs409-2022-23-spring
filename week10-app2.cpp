// Function objects, operator() overloads and multiple inheritance
// lambda equivalents and the "struct overloaded { ... }" trick
// deduction guide to the rescue

#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

struct FuncObjInt    { void operator() (int i) const           { cout << "Int version: " << i << endl;    } };
struct FuncObjFloat  { void operator() (float f) const         { cout << "Float version: " << f << endl;  } };
struct FuncObjString { void operator() (const string& s) const { cout << "String version: " << s << endl; } };

// inherit from 3 different function objects and create 1 new FO that can act to its input parameter type via overload resolution
//struct MyFuncObjGeneric : FuncObjInt, FuncObjFloat, FuncObjString
//{
//    using FuncObjInt::operator (), FuncObjFloat::operator (), FuncObjString::operator ();
//};

// let's write it extra generic
template<typename ... Ts>
struct FuncObjGeneric : Ts... { using Ts::operator()...; };

using MyFuncObj = FuncObjGeneric<FuncObjInt, FuncObjFloat, FuncObjString>;


auto l1 = [](int i)            { cout << "Int version: " << i << endl;    };
auto l2 = [](float f)          { cout << "Float version: " << f << endl;  };
auto l3 = [](const string& s)  { cout << "String version: " << s << endl; };


// OVERLOADED support starts
template<typename ... Ls> struct overloaded : Ls... { using Ls::operator()...; };

// write a deduction guide so that decltype(l1), decltype(l2), decltype(l3) are automatically deduced
// from constructor to template parameters of the class

template<typename ... Ls>
overloaded(Ls ... ls) -> overloaded<Ls...>;
// OVERLOADED support ends

int main()
{
//    auto fo = MyFuncObj{};
//    fo(5); // call it with an integer
//    fo(1.1f); // call it with an float
//    fo("Hi there"); // call it with const char[9] ---> const char * --->  supplied into string c-tor

    //auto l = overloaded<decltype(l1), decltype(l2), decltype(l3)>{l1, l2, l3};

    auto l = overloaded{l1, l2, l3};
    l(5); // call it with an integer
    l(1.1f); // call it with an float
    l("Hi there"); // call it with const char[9] ---> const char * --->  supplied into string c-tor

    return 0;
}
