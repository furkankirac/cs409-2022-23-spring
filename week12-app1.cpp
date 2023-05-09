// std::integral_constant, std::true_type, std::false_type, tag dispatching

// constexpr functions
// std::is_constant_evaluated()

// godbolt.org
// factorial function that runs at compile time
// - with integral_constant
// - with constexpr

// decltype(auto)

#include <iostream>
#include <string>

using namespace std;

struct LoggingMode { };
struct ReleaseMode { };

template<typename T, T v>
struct IntegralConstant {
    using value_type = T;
    static constexpr T value = v;
};

using TrueType = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;

//struct XYZ
//{
//    using value_type = bool;
//    static constexpr bool value = true;
//};

void foo(const string& s, TrueType) { cout << s << ": logging mode" << endl; }
void foo(const string& s, FalseType) { cout << s << ": release mode" << endl; }

template<typename T>
void bar(const string& s, T)
{
    if constexpr(is_same_v<T, LoggingMode>)
        cout << s << ": logging mode" << endl;
    else if constexpr(is_same_v<T, ReleaseMode>)
        cout << s << ": release mode" << endl;
}

int main() {

//    auto k = int_10::value_type{};
//    auto m = int_10::value;

    int a = 10;

    bool b = true;
    auto boolean_true = IntegralConstant<bool, true>{};
    auto boolean_false = IntegralConstant<bool, false>{};

    foo("Hello", TrueType{});
    foo("Hello", FalseType{});

    bar("Hello", LoggingMode{});
    bar("Hello", ReleaseMode{});

    return 0;
}
