// overload resolution done by the compiler is a functional-programming asset

// new/alternative style return type declaration

// initializer_list
// overloading casting operator

// generic structs with internal typename aliases and static/const/constexpr values

// Containers

// concepts
//template <typename T>
//concept Container = requires(T t) {
//    typename T::value_type;
//    typename T::size_type;
//    typename T::iterator;
//    typename T::const_iterator;
//    { std::begin(t) } -> std::same_as<typename T::iterator>;
//    { std::end(t) } -> std::same_as<typename T::iterator>;
//    { t.size() } -> std::same_as<typename T::size_type>;
//    { t.empty() } -> std::same_as<bool>;
//};

// template parameter types: unknown typename, known typename with a value
// auto in templates

// std::pair, std::tuple, std::map


#include <iostream>

using namespace std;

template<typename T>
class Foo {
    T value = 0;

public:
    T& get() { return value; }

    Foo() { }
    Foo(const T& i) : value{i} { }
    Foo(T&& i) : value{std::move(i)} { }

    Foo(std::initializer_list<T> il) : value{il.begin()[0]} { //
        cout << "init list has been selected" << endl;
        cout << il.begin() << endl;
        cout << il.size() << endl;
        cout << "First element is " << il.begin()[0] << endl;
        cout << "Second element is " << il.begin()[1] << endl;
    }

    explicit operator double() const
    {
        cout << "I am being cast to double" << endl;
        return value;
    }

    explicit operator int() const
    {
        cout << "I am being cast to int" << endl;
        return value;
    }

    Foo(const Foo& other) { } // copy ctor
    Foo(Foo&& other) { } // move ctor // this binds to an r-value at the call site

    Foo& operator=(const Foo& other) { return *this; }; // copy assignment
    Foo& operator=(Foo&& other) { return *this; }; // move assignment  (this is a Foo*)
};



auto foo() -> float // new style return type definition
{
    return 3.4f;
}

#include <vector>

int main(int argc, char* argv[])
{
    auto vec1 = std::vector<int>{5}; // vector with a single element that is 5
    auto vec2 = std::vector<int>(5); // vector with 5 integers default constructed to 0

    auto f1 = Foo<int>{};
    auto f2 = Foo<int>{};
    auto f3 = Foo<int>{};

    f1 = f2; // l-value = l-value ---> chooses "void operator=(const Foo& other)"
    f1 = f2 = f3;

    auto f4 = Foo<float>{11.14f, 2.2f, 5.5f};

    auto& v = f4.get();
    cout << v << endl;

    v = 5.5f;

    cout << f4.get() << endl;

    cout << (double)f4 << endl;
    cout << (int)f4 << endl;
//    operator double(f4)


    return 0;
}

