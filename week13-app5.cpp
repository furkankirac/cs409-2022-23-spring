// = default, = delete, std::declval
// [[nodiscard]]

// unique_ptr, shared_ptr

// duck typing? type erasure: std::function
// if something walks like a duck, quacks like a duck, then it is a duck!

// SFINAE: enable_if, and its relation with concepts

// ADL: argument dependent lookup, friend functions

// CRTP: curiously recurring template pattern

#include <iostream>

using namespace std;

template<bool B, typename T = void> struct enableIf { };
template<typename T>                struct enableIf<true, T> { using type = T; };

template<typename T>
concept IsIntegral = is_integral_v<T>;

//template<typename Integral, typename T = enableIf< is_integral_v<Integral> >::type >
//void printIntegralValues(Integral integral)
//{
//    cout << integral << endl;
//}

template<typename Integral>
enableIf< is_integral_v<Integral> >::type printIntegralValues(Integral integral)
{
    cout << integral << endl;
}


void foo(int* = nullptr)
{
}

int main()
{
    // SFINAE -> Substitution Failure Is Not An Error
    // invented trick to earn the concept like behavior with old compilers
    // have concepts before they are introduced in C++20

//    printIntegralValues("Hi there"); // invalid
    printIntegralValues(3); // valid
    foo();

}
