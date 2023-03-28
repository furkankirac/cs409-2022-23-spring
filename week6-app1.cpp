// type displayer debugging trick for generic types

// value categories: l-value + r-value
// forwarding references T&&
// const T&&?

// refness captured in a generic type
// reference collapsing rules

// perfect forwarding

#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!


template<typename T>
struct TypeDisplayer; // forward declaration

//void foo(float& value) { cout << "l-value" << value << endl; }

//// although the input parameter is an r-value at call site, we gave it a name "value"
//// it became an l-value within the context of this function
//void foo(float&& value)
//{
//    cout << "r-value" << value << endl;
//    // we need to force it ourselves so that it becomes an r-value again
//    // because we already know that it is an r-value at call site
//    // otherwise this function would have never been called due to the "float&&" signature.
//    bar(std::move(value)); // equivalent to writing bar((float&&)value);
//}

//// binds to both l-value and r-values but it cannot change the contents of the bound variable
//void foo(const float& value)
//{
//    cout << "l or r-value" << value << endl;
//}


//template<typename T>
//void foo(T& value) // l-value only binding ref
//{
////    auto t = TypeDisplayer<T>{};
//    cout << "l-value" << endl;
//}

void bar(float& value) { } // binds to only r-values
void bar(float&& value) { } // binds to only r-values


template<typename T>
void foo(T&& value) // forwarding ref ---> Scott Meyer's Universal References
{
    // template type deduction mechanism chooses T to be float&
    // float& && ---> reference collapsing rules ---> float&

    // l-value scenario -> T is float&
    // r-value scenario -> T is float

    // if T includes refness then the call site value is an l-value
    // if T includes no refness then the call site value is an r-value

//    auto t = TypeDisplayer<T>{};

    value = 10.10f;

    // std::forward is a conditional r-value ref cast by looking at T's refness it decides
    bar(std::forward<T>(value));

//    if constexpr(...) {
//        bar(std::move(value));
//    } else {
//        bar(value); // value is l-value
//    }

    cout << "forwarding ref" << endl;
}


//void foo(const int& value) // both l-value and r-value binding ref
//{
//    cout << "const version" << endl;
//}


int main(int argc, char* argv[])
{
//    TypeDisplayer<int> a; // old style
//    auto a = TypeDisplayer<int>{};

    float f = 5.5f;
    foo(5.5f);
    std::cout << f << endl;

//    using Float = float;

//    using FloatRef = float&;
//    using FloatRefRef = float&&;
//    auto t = TypeDisplayer< FloatRef & >{};       // ---> float &;
//    auto t = TypeDisplayer< FloatRef && >{};      // ---> float &;
//    auto t = TypeDisplayer< FloatRefRef & >{};    // ---> float &;
//    auto t = TypeDisplayer< FloatRefRef && >{};   // ---> float &&;

    return 0;
}
