// std::pair, std::tuple, std::map
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>
#include <string>
#include <map>

using namespace std;

// std::pair;
template<typename First, typename Second>
struct Pair {
    First first;     // first attribute
    Second second;   // second attribute
};

//template<typename First, typename Second, typename Third>
//struct Triple {
//    First first;     // first attribute
//    Second second;   // second attribute
//    Third third;
//};

// std::tuple is the most generic struct creator on the fly for generic programming

enum Genre { Horror, SciFi, Drama };
struct Movie
{
    int date;
    Genre genre;
    string director;
};


template<typename T>
struct Debug;

int main(int argc, char* argv[])
{
    auto m = std::map<int, string>{ // string has a c-tor with a "const char *"
        {5, "Five"}, // int, const char[4+1] -> const char*
        {10, "Ten"}, // int, const char[3+1] -> const char*
    };

//    for(const auto it = std::begin(m); it != std::end(m); it++) {
//        const auto& item = *it;
//        // ...
//    }

    // c++: structured binding
    // deconstructing in javascript/typescript
    for(auto&& [key, value] : m) { // type of the item?   std::pair<int, string>
        cout << "key=" << key << "  " << "Value = " << value << endl;
    }

    using MovieAsTuple = std::tuple<int, Genre, string, string>;

    auto movie = MovieAsTuple{2023, SciFi, "Nuri Bilge Ceylan", "HiThere"};
    cout << "Director is " << std::get<2>(movie) << endl;
    cout << "Director is " << std::get<3>(movie) << endl;

//    using T = std::tuple_element_t<2, MovieAsTuple>;
//    auto dbg = Debug<T>{};


//    auto mypair = Pair<int, double>{10, 5.5};
//    cout << "first = " << mypair.first << endl;
//    cout << "second = " << mypair.second << endl;

    return 0;
}
