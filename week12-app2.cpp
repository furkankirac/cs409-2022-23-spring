#include <type_traits>

// factorial implementation with meta programming
// even at debug mode it creates compile-time code
template<int N>
struct factorial_v1 {
    static constexpr auto value = N * factorial_v1<N-1>::value;
};

template<>
struct factorial_v1<0> {
    static constexpr auto value = 1;
};

// factorial implementation similar to above but with using already available integral_constant class
// for storing values at compile-time as types
// even at debug mode it creates compile-time code
template<int N>
struct factorial_v2 : std::integral_constant<int, N * factorial_v2<N-1>::value> {};
template<>
struct factorial_v2<0> : std::integral_constant<int, 1> {};

// constexpr version of the factorial
// demands c++14 onward
// you need to forcefully use it within constexpr context otherwise it falls back to runtime code generation
// if the runtime code optimizer of the compiler cannot behave clever enough
constexpr int factorial(int n) {
    // ask the compiler if current code is running in constexpr context or runtime context
    // you can behave differently depending on that
    if(std::is_constant_evaluated()) return -1;

    // recursive implementation
    if(n == 0) return 1;
    return n * factorial(n-1);

    // standard implementation
    // int product = 1;
    // for(int i=2; i<=n; i++) product *= i;
    // return product;
}

int main()
{
    constexpr int a = factorial(5); // compile-time calculation of 5!
    return a;

    // factorial is called with run-time context
    // if optimizer is not clever enough it might generate runtime code
    // current compilers are clever enough to optimize this to compile time context though
    return factorial(5);

    // even in debug mode, you'll get compile-time evaluation
    return factorial_v1<5>::value; // 120
    return factorial_v2<5>::value; // 120
}
