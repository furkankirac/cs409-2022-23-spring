// variadic templates, parameter packs, pack expansions (C++11 and later) "modern C++"
// - write an add function that adds all its input parameters

// fold expressions (C++17 and later) "more modern C++" ---> "modern C++"
// - write an add function that adds all its input parameters with fold expressions

// fold expressions and comma operator
// - write a print(...) function that prints all its input arguments to the console

// std::pair, std::tuple, std::map
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>

using namespace std;

// parameter pack is not an array!
// parameter pack is a conceptual internal representation of a lot of things as if they are zipped (archived)

template<typename ... Ts> // types flow from the compile-time world into a "type parameter pack" named Ts
auto add_v2(Ts&& ... ts) // ts = "5|10|20|-5|3.2|-5.8f" (again a parameter pack but this time value ppack)
{
    return (forward<Ts>(ts) + ...); // fold expression
    //    return (5 + 10 + 20 + (-5) + 3.2 + (-5.8f)); // fold expression
    //    return (... + ts); // fold expression in reverse order

    // it needs to be within paranthesis
    // there needs to be a value parameter pack somewhere in there
    // there needs to be an operator in between the ellipsis (...) operator
}

//auto add_v1() { return 0; }

template<typename First, typename ... Rest> // First = int, Rest = "int|int|int|double|float"
auto add_v1(const First& first, const Rest& ... rest) // first=5, rest = "10|20|-5|3.2|-5.8f"
{
    if constexpr(sizeof...(Rest) == 0) {
        return first;
    }
    else {
        return first + add_v1(rest...); // rest... is parameter pack expansion by putting , in between
    }
//    (10|20|-5|3.2|-5.8f)... --> 10,20,-5,3.2,-5.8f
}

//template<typename ... Ts>
auto add_v3(auto&& ... ts) {
    return (forward<decltype(ts)>(ts) + ...);
}

auto comma()
{
    return (10, 15, 16, 20);
}

auto return_last_value_of(auto&& ... ts)
{
    return (ts, ...);
}

void print(auto&& ... ts)
{
    cout << "Now printing all input arguments" << endl;
    ((cout << ts << endl), ...);
//    (cout << 5 << endl), (cout << 10 << endl), ..., (cout << -5.8f << endl);
    cout << endl;
}


int main(int argc, char* argv[])
{
    int five = 5;

    auto addition = add_v2(five, 10, 20, -5, 3.2, -5.8f); // Ts = "int|int|int|int|double|float"

    cout << "Last element is " << return_last_value_of(five, 10, 20, -5, 3.2, -5.8f) << endl;


    print(five, 10, 20, -5, 3.2, -5.8f);

    cout << comma() << endl;

    cout << add_v3(10, 20) << endl;

    (cout << addition << endl), (cout << addition << endl);

// comma operator working in C
//    int a=5, c=10, d=20;
//    for(int i=0, j=0; i<10; i++, j+=2) {
//    }



//    cout << add(10, 20) << endl;
//    cout << add(-5.5, -6.6, 10) << endl;

    return 0;
}
