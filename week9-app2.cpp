// Function objects, operator() overloads and multiple inheritance
// lambda equivalents and the "struct overloaded { ... }" trick

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors
// Array<T, sz> implementation with deduction guides

#include <iostream>

using namespace std;

struct FunctionObject
{
    int i;
    float f;

    void operator() (int howMany) const
    {
        for(auto k=0; k<howMany; k++) {
            cout << i << endl;
            cout << f << endl;
        }
    }
};

int main()
{
    auto funcObj = FunctionObject{10, 22.2f};
//    funcObj.operator()(3);
//    funcObj(3);

    auto lambda = [i=10, f=22.2f](int howMany)
    {
        for(auto k=0; k<howMany; k++) {
            cout << i << endl;
            cout << f << endl;
        }
    };
    lambda(3);

    return 0;
}
