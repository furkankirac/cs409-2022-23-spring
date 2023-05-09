// decltype(auto)

// get_int_byval(), get_int_byref()
// function object that calls the callable when called :)

// lambdas capturing local variables: this includes local parameter packs as well
// storing parameter packs: an elegant storage container; get_first, get_size, get_tail impl.

// helper tips:
// struct in struct helps when the parent struct is templated
// a lambda in a function with a fold expression

#include <iostream>

using namespace std;

auto get_int_byval() -> int  { int i = 5; return i; }
auto get_int_byref() -> int& { static int i = 5; return i; }

struct Func
{
    template<typename Callable>
    auto operator() (Callable callable) const {
        return callable();
    }
};

//auto func = []<typename Callable>(Callable callable) { return callable(); };
//auto func = [](auto callable) { return callable(); };

template<typename...>
struct Debug;

int main() {
    auto i1 = get_int_byval(); // int
    auto i2 = get_int_byref(); // int
    // auto is focused on the value's type
    // auto does not care how the value is pointed to
    // either through a ref or the value itself, it doesn't make a difference for auto
    // auto gets the type of the value

    decltype(auto) i3 = get_int_byval(); // int
    decltype(auto) i4 = get_int_byref(); // int&

    auto func1 = Func{};
    decltype(auto) j1 = func1(&get_int_byval); // int
    decltype(auto) j2 = func1(&get_int_byref); // int

    auto func2 = [](auto callable) -> decltype(auto) {
        return callable();
    };
    decltype(auto) k1 = func2(&get_int_byval); // int
    decltype(auto) k2 = func2(&get_int_byref); // int&
//    auto dbg = Debug<decltype(k2)>{};

    return 0;
}
