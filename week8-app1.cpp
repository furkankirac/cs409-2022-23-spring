// template parameter types: unknown typename, known typename with a value, auto in templates as a parameter

// variadic templates, parameter packs, pack expansions (C++11 and later)
// - write and add function that adds all its input parameters

// fold expressions (C++17 and later)
// - write and add function that adds all its input parameters with fold expressions

// fold expressions and comma operator
// - write a print(...) function that prints all its input arguments to the console

// std::pair, std::tuple, std::map
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>

using namespace std;


template<typename Whatever> // it has a single parameter and it's a type-name
void foo(Whatever whatever) { cout << "foo has been called" << endl; }

void foo2(auto whatever) { cout << "foo2 has been called" << endl; }

template<typename T>
concept isIntegral = std::is_integral<T>::value;

template<typename T, T value>
void bar() {
    if constexpr( isIntegral<T> ) { // compile time branching
        cout << "This is an integral type: ";
    }

    cout << "bar has been called and the value is " << value << endl;
}

void bar_int_5() {
    cout << "This is an integral type: ";
    cout << "bar has been called and the value is 5" << endl;
}

void bar_double_5_5() {
    cout << "bar has been called and the value is 5.5" << endl;
}


template<auto value>
void bar2() {
    using T = decltype(value);

    if constexpr( isIntegral<T> ) {
        cout << "This is an integral type: ";
    }

    cout << "bar2 has been called and the value is " << value << endl;
}

void bar2_int5() {
    cout << "bar2 has been called and the value is 5" << endl;
}


int main(int argc, char* argv[])
{
    foo<int>(5);
    foo(5); // auto deduction by means of looking at the input parameters

    foo2<int>(5);
    foo2(5);

    bar<int, 5>();
    bar_int_5();

    bar2<5>(); // this is an integral typed value: 5 is an integer. integer is an integral type
    bar2<5.5>(); // 5.5 is a double, which isn't an integral type

    return 0;
}
