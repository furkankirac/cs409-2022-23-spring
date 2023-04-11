// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>
#include <string>
#include <map>
#include <tuple>

using namespace std;

// I am interested in getting the type in a-lot-of-types (variadic number of types) at a specific index

// base case of my template specialization
template<size_t index, typename ... Ts>
struct nth_type;

template<typename First, typename ... Rest>
struct nth_type<0, First, Rest...> {
    using type = First;
};

template<size_t N, typename First, typename ... Rest>
struct nth_type<N, First, Rest...> {
    using type = typename nth_type<N-1, Rest...>::type;
};



template<size_t N, typename ANYTUPLE>
struct nth_tuple_type;

template<size_t N, typename ... Ts>
struct nth_tuple_type<N, std::tuple<Ts...>>
{
    using type = typename nth_type<N, Ts...>::type;
};


template<typename ...>
struct Debug;

// Remember that there are different standard library implementations
// 1) libstdc++: GNU GCC implementation and uses C++98 (1998) why? to be compatible with archaic chips
//               such as microcontrollers
// 2) libc++:    Apple's implementation for Clang uses C++11 (2011)

// if you are using GCC, it doesn't mean that you must use C++98 version libstdc++
// you can switch it to libc++ as well!

int main(int argc, char* argv[])
{
    using T = nth_type<4, float, double, float, double, int, string>::type; // shall return float
    // T shall be float

    using mytuple = std::tuple<float, double, float, double, int, string>;
    using TT = nth_tuple_type<0, mytuple>::type;
//    auto d = Debug<TT>{};

    static_assert(std::is_same_v<float, nth_tuple_type<0, mytuple>::type>, "0th index error");

    return 0;
}
