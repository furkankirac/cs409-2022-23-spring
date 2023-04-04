// generic structs with internal typename aliases and static/const/constexpr values

// Containers

// template parameter types: unknown typename, known typename with a value
// auto in templates

// std::pair, std::tuple, std::map


#include <iostream>
#include <vector>
#include <list>

using namespace std;


// concepts
template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::size_type;
    typename T::iterator;
    typename T::const_iterator;
    { std::begin(t) } -> std::same_as<typename T::iterator>;
    { std::end(t) } -> std::same_as<typename T::iterator>;
    { t.size() } -> std::same_as<typename T::size_type>;
    { t.empty() } -> std::same_as<bool>;
};


template<typename T1, typename T2> struct IsSame { static const bool value = false; };
// partial template specialization
template<typename K> struct IsSame<K, K> { static const bool value = true; };

//struct IsSame_int_float { static const bool value = false; };
//struct IsSame_int_int { static const bool value = true; };

template<typename T>
struct Value
{
//    struct iterator {

//    };

    using value_type = T;

    T value;
    operator T() const { return value; }
//    Value(const T& value) : value{value} { }
};


template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2)
{
    if constexpr(Container<T1> && Container<T2>) {
        auto newContainer = t1;

        auto it1 = begin(newContainer);
        auto it2 = begin(t2);
        while(it1 != end(newContainer)) {
            (*it1) += *it2;
            it1++;
            it2++;
        }
        return newContainer;
    } else if constexpr(std::is_same_v<T1, T2>) {
        return t1 + t2;
    } else
    {
        cout << "Error: adding different types" << endl;
        return t1;
    }

}


int main(int argc, char* argv[])
{
    cout << ((IsSame<int, int>::value) ? "true" : "false") << endl;
    cout << ((IsSame<int, float>::value) ? "true" : "false") << endl;
//    cout.operator <<(IsSame<int, int>::value)

    cout << add(3, 5) << endl;
    cout << add(3, 5.5) << endl;

//    Value<int>{3};
    cout << add(Value<int>{3}, Value<double>{5.5}) << endl;

    // What is a container?
    // Containers are the structures that has:
    // begin() method (which returns iterator to first element),
    // end() method (which returns iterator to a conceptual location that is after the last element),
    // size() method that returns the number of elements in the container
    // in addition, the iterators need to support some iteration capability

    auto v = std::list<float>{1, 2, 3, 4};
    auto v2 = std::list<float>{1.1, 2.2, 3.3, 4.4};
//    for(auto it = begin(v); it != end(v); it++) {
//        cout << *it << ", ";
//    }
    for(const auto& item : v)
        cout << item << ", ";

    cout << endl;

    auto v_result = add(v, v2);
    for(const auto& item : v_result)
        cout << item << ", ";



    return 0;
}

