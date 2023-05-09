// lambdas capturing local variables: this includes local parameter packs as well
// storing parameter packs: an elegant storage container; get_first, get_size, get_tail impl.

// helper tips:
// struct in struct helps when the parent struct is templated
// a lambda in a function with a fold expression

#include <iostream>

using namespace std;

//template<typename ItemType>
//struct Container
//{
//    struct Iterator
//    {

//    };
//};

auto list(auto&& ... ts)
{
    return [ts...](auto accessor) {
        return accessor(ts...);
    };
}

auto get_first()
{
    return [](auto&& first, auto&& ... rest) {
        return first;
    };
}

auto get_tail()
{
    return [](auto&& first, auto&& ... rest) {
        return list(rest...); // rest... ----> 1, 'a', "abc", 3.14
    };
}

auto get_last()
{
    return [](auto&& first, auto&& ... rest) {
        return (rest, ...); // return 'z', 1, 'a', "abc", 3.14
    };
}


struct Lambda
{
    int& k; // this is a pointer/reference (an address to memory)
    Lambda(int& k) : k(k) { }
    auto operator() (int increment) const { k += increment; }
};

#include <vector>

template<typename T>
concept Container = requires (T t) {
    t.begin();
    t.end();
    t.size();
};

void print(Container auto&& container)
{
    for(auto&& item : container)
        cout << item << " ";
    cout << endl;
}

void print(auto&& ... params)
{
    auto print_ = [](auto&& item) {
        cout << item << " ";
    };

    (print_(params), ...);
}

int main() {
    auto v = vector{1, 2, 3, 4};

    auto z = 'z';
    auto l = list(z, 1, 'a', "abc", 3.14);

    auto a = l(get_first());
    cout << a << endl;

    auto l_tail = l(get_tail());
    auto b = l_tail(get_first());
    cout << b << endl;

    auto c = l(get_last());
    cout << c << endl;

    int k = 10;
    auto lambda = [&k](int increment) { k += increment; };
    lambda(100);
    cout << k << endl;

    return 0;
}
