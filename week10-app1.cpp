// function templates are auto type deducible with function parameter bindings
// class templates are not that easy to auto deduce the types.
// we need deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from class constructors
// - Array<T, size> implementation with deduction guides

#include <iostream>
#include <initializer_list>

using namespace std;

                     void foo(auto t) { }
template<typename T> void foo() { if constexpr (is_same_v<T, int>) cout << "integer" << endl; }

template<typename T, size_t size>
struct Array
{
    T values[size];

    // initializer list: .size() method is happening at run-time (we don't know constexpr yet)
    // parameter pack
    template<typename ... Args>
    Array(Args&& ... args) : values{std::forward<Args>(args)...}
    {
    }

    void print() const
    {
        for(auto i=0; i<size; i++)
            cout << values[i] << endl;
    }
};

template<typename First, typename ... Rest>
Array(const First& first, Rest&& ... rest) -> Array<First, 1 + sizeof...(rest)>;

int main()
{
//    foo<int>(11); // auto type deduced 11 --> int
//    foo(11); // auto type deduced 11 --> int
//    foo<int>(); // writes integer
//    foo<float>(); // writes nothing

    int a = 10;
    auto array = Array{a, 20, 30, 40, 50, 60, 70};
    array.print();

    return 0;
}
