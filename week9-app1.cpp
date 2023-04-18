// inline functions

// print reverse
// 1) with if constexpr: First, Rest... trick
// 2) with fold expressions: a trick where a hidden feature of the language is utilized

// concepts
// requires clause
// requires expression
// --- CastableToInt

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors
// Array<T, sz> implementation with deduction guides

// Function objects, operator() overloads and multiple inheritance
// lambda equivalents and the "struct overloaded { ... }" trick

#include <iostream>

using namespace std;

inline void bar()
{
    cout << "There" << endl;
}

inline void foo(int i, int j, int k)
{
    cout << "Hi" << endl;
    bar();
}

//template<typename First, typename ... Rest>  // int|float|float|int|const char[10]
//inline void print(First&& first, Rest&& ... rest) // 5|5.5f|1.1f|10|"Hi there."
inline void print(auto&& first, auto&& ... rest) // 5|5.5f|1.1f|10|"Hi there."
{
    if constexpr(sizeof...(rest) > 0)
        print(rest...);
    cout << first << endl;
    // ts...; // parameter pack expansion. this expands by putting commas in between
    // IMPORTANT: The commas here are not COMMA OPERATORS!!!!
    // dummy(ts...);
}

// concepts are compile time predicates
// predicates are things that return boolean

template<typename T>
concept CastableToInt = requires(T t) { // requires expression
    (int)t;
};

void print_foldexp(CastableToInt auto&& ... values)
{
//    int a=10, b=20, c=30;
//    a = b = c = 40;
//    // c=40 is calculated, c is returned
//    a = b = c;
//    // b=c is calculated, b is returned
//    a = b;
//    // a=b is calculated, a is returned
//    a;

//    // this is okay!
//    struct Dummy { };
//    auto d1 = Dummy{};
//    auto d2 = Dummy{};
//    d1 = d2;

    struct Dummy { };
    ( ( (cout << values << endl), Dummy{}) = ...);
//    (cout << 5 << endl), (cout << 5.5f << endl), (cout << 1.1f << endl), (cout << 10 << endl), (cout << "Hi there." << endl);
//    (..., (cout << values << endl));
}



int main()
{
//    print(5, 5.5f, 1.1f, 10, "Hi there.");
    print_foldexp(5, 5.5f, 1.1f, 10); //, "Hi there.");
//    (int)"Hi there.";
//    {
//        cout << "Hi there." << endl;
//        cout << 10 << endl;
//        cout << 1.1f << endl;
//        cout << 5.5f << endl;
//        cout << 5 << endl;
//    }


//    for(auto i=0; i<1000; i++) {
//        bar();
//        foo(1, 2, 3);
//    }
    return 0;
}
