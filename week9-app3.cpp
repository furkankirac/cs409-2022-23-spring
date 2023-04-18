// Function objects, operator() overloads and multiple inheritance
// lambda equivalents and the "struct overloaded { ... }" trick

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors
// Array<T, sz> implementation with deduction guides

#include <iostream>
#include <string>

using namespace std;

struct FunctionObjectInt
{
    void operator() (int i) const { cout << "Int version: " << i << endl; }
};

struct FunctionObjectFloat
{
    void operator() (float f) const { cout << "Float version: " << f << endl; }
};

struct FunctionObjectString
{
    void operator() (const string& s) const { cout << "String version: " << s << endl; }
};


struct FunctionObjectGeneric : FunctionObjectInt, FunctionObjectFloat, FunctionObjectString
{
    using
        FunctionObjectInt::operator (),
        FunctionObjectFloat::operator (),
        FunctionObjectString::operator ();
};


template<typename ... Ts>
struct FunctionObjectGenericWithTemplates : Ts...
{
    using Ts::operator()...;
};

struct FunctionObjectGeneric_v2
{
    void operator() (int i) const { cout << "Int version: " << i << endl; }
    void operator() (float f) const { cout << "Float version: " << f << endl; }
    void operator() (const string& s) const { cout << "String version: " << s << endl; }
};

int main()
{
    auto funcObjVeryGeneric = FunctionObjectGenericWithTemplates<
        FunctionObjectInt,
        FunctionObjectFloat,
        FunctionObjectString>{};


//    int a = 5;
//    switch(a) {
//    case 1: ...; break;
//    case 2: ...; break;
//    case 5; ...; break;
//    }


//    funcObjVeryGeneric(10);


    auto fobj_int = FunctionObjectInt{};
    fobj_int(10);

    auto fobj_float = FunctionObjectFloat{};
    fobj_float(1.1f);

    auto fobj_string = FunctionObjectString{};
    fobj_string("Hi there!");

    auto fobj = FunctionObjectGeneric{};
    fobj(10);
    fobj(1.1f);
    fobj("Hi there!");

    auto fobj2 = FunctionObjectGeneric_v2{};
    fobj2(10);
    fobj2(1.1f);
    fobj2("Hi there!");

    return 0;
}
