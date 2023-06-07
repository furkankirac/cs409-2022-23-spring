// Ozyegin University 2022-23 Spring Term CS409/509 Takehome Exam 2
// This exam contains different flavors of some questions for CS409 and CS509 students

// !!!!!!!!!! FILL-IN BELOW TWO LINES !!!!!!!!!!!!!!
// STUDENT NUMBER: ......
// STUDENT NAME: ........

// All the takehome exam 2 is in this file. There is no extra file for the exam.
// !!!!!!!!!! READ THIS FILE FULLY AND VERY CAREFULLY BEFORE STARTING YOUR SOLUTIONS. !!!!!!!!!!

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// THIS IS AN OPEN EXAM. YOU CAN USE GPT-4, ALL AVAILABLE LITERATURE, ETC.
// BUT YOU NEED TO SOLVE THE EXAM PERSONALLY YOURSELF.
// YOU CANNOT GET HELP FROM REAL PERSONS DIRECTLY OR INDIRECTLY.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// YOU MIGHT BE SELECTED FOR AN ORAL EXAM AND BE WANTED TO MANIPULATE YOUR OWN SUBMITTED CODE.
// THIS IS PART OF THE SYLLABUS.
// ANY MAJOR FAILURE IN THE ORAL EXAM WILL CAUSE A DISCIPLINARY ACTION.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// YOU MUST USE GCC 12+ with C++20 dialect. Any other compiler and dilect usage will not be checked.
// YOUR CODE MUST COMPILE UNDER ABOVE SETTINGS

// Questions about the exam can be asked to your instructor and TA by emailing them at the same time
// mail to: furkan.kirac@ozyegin.edu.tr and doga.yilmaz.11481@ozu.edu.tr
// at the same time.
// Email responses will be given at worst by 21:00 in the same day.
// You asked at 13:45, you are answered by 21:00 that day.
// You asked at 21:15, you are answered by 21:00 the NEXT day.
// You cannot ask questions about the exam to anybody else.

// Now have a look at the main() function first,
// The questions are located there as well.
// Then start solving all the questions between the indicated space below with "WRITE YOUR CODE HERE" markers.

#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <array> // used by CS509 related question
#include <string>

using namespace std;

// ---------------- WRITE YOUR CODE HERE (BEGIN)



// ---------------- WRITE YOUR CODE HERE (END)

int main() {
    {
        // Q1) 20 pts
        // Write a bind function that starts binding to the parameters of an already available callable
        // Completing all the necessary parameters makes bind function call the original function with all params
        // and return the result.
        // Any incomplete bind function returns a lambda that waits for extra parameters to be added by calling it
        // This goes on until all the parameters are completed, then it calls the original function and returns the result if any

        auto add = [](int x, int y, int z) { return x + y + z; };
        const auto val1 = bind(add, 1, 2, 3); // 1+2+3=6
        const auto val2 = bind(add, 1, 2)(3); // 1+2+3=6
        const auto val3 = bind(add, 1)(2)(3); // 1+2+3=6
        const auto val4 = bind(add)(1)(2)(3); // 1+2+3=6
        cout << val1 << "," << val2 << "," << val3 << "," << val4 << endl;
    }

    {
        // Q2) 20 pts
        // We know that there is a "virtual function" support in core C++ language.
        // We also know that there is type-erasure support by means of std::function in C++ standard library.
        // Without using virtual or std::function; write an Animal struct that makes the below code work properly.
        struct Cow   { void speak() const { cout << "Moo" << endl; } };
        struct Sheep { void speak() const { cout << "Mee" << endl; } };

        auto do_animal_things = [](Animal animal) { animal.speak(); };
        do_animal_things(Animal{Cow{}});   // writes Moo
        do_animal_things(Cow{});           // writes Moo
        do_animal_things(Animal{Sheep{}}); // writes Mee
        do_animal_things(Sheep{});         // writes Mee
    }

    {
        // Q3) 10 pts
        // A std::tuple is a heterogenous container that can store arbitrary number of types and their corresponding values.
        // auto tpl = make_tuple(1, string("hi"), 3.14) is a 3 dimensional compile-time heterogenous vector
        // it's 1st dimension's type is int, 2nd string, 3rd double
        // they have respective values 1, "hi", 3.14.
        // Write for_each_tuple_item function that traverses the elements/dimensions of a given tuple and passes it to
        // a supplied function "func".
        // This function must be protected by a "requires" clause so that it will be only available for tuple params
        // "concept" core language keyword usage is FORBIDDEN.
        // You must use inline requires expressions and clauses.

        // Q4) 20 pts
        // Write "filter_tuple" algorithm that takes a std::tuple and a function that returns true/false on a dimension of tuple.
        // This algorithm must filter the tuple and return a new tuple with filtered out dimensions and their respective values
        // This function must be protected by a "requires" clause so that it will be only available for tuple params
        // "concept" core language keyword usage is FORBIDDEN.
        // You must use inline requires expressions and clauses.
        // You can write your own is_tuple/is_tuple_v structs if necessary

        // Q5) 20 pts
        // Write a generic filter function that can filter tuples, and containers
        // CS409: (12 pts) tuple, (5 pts) vector, (3 pts) list supports are sufficient
        // CS509: (10 pts) tuple, (1 pts) vector, (1 pts) list, (8 pts) array supports are sufficient

        // Q6) 10 pts
        // Write a generic print function that can print containers, tuples, or any other primitives that are sendable to std::cout
        // Your generic print function must also support variadic number of arguments as illustrated in the below code.

        // DO NOT EVER CHANGE THE CODE IN MAIN
        // THERE IS ONE EXCEPTION FOR CS509 students where they must comment out the respective question below

        auto tpl = make_tuple(
                [](auto a, auto b) { return a + b; },
                10,
                25,
                42.42,
                "Hello",
                string("there")
            );
        auto tpl_type_filtered = filter(tpl, []<typename T>(const T&) { return is_integral_v<T>; } );

        for_each_tuple_item(tpl, []<typename T>(const T& item) {
            if constexpr(is_integral_v<T>)
                cout << item << endl;
        });

        auto v = vector{10, 25, 101, 1001};
        auto v_filtered = filter(v, [](int val) { return val > 100; } );
        auto l = list{10.10, 25.25, 101.101, 1001.1001};
        auto l_filtered = filter(l, [](int val) { return val > 100.0; } );
        // CS509 students can uncomment the below code
        // auto a = array<int, 4>{10, 25, 101, 1001};
        // auto a_filtered = filter(a, [](int val) { return val > 100; } );
        // print("a_filtered", a_filtered); // will print "a_filtered" = { 101 1001 }

        print(
            "v", v,
            "v_filtered", v_filtered,
            "l", l,
            "l_filtered", l_filtered,
            "tpl_type_filtered", tpl_type_filtered
            );
    }
}
// CONSOLE OUTPUT WILL BE AS BELOW FOR CS409 students.
// For CS509 students there will be one extra line "a_filtered" = { 101 1001 } in respective location. Look at above code.

// 6,6,6,6
// Moo
// Moo
// Mee
// Mee
// 10
// 25
// "v" = { 10 25 101 1001 }
// "v_filtered" = { 101 1001 }
// "l" = { 10.1 25.25 101.101 1001.1 }
// "l_filtered" = { 101.101 1001.1 }
// "tpl_type_filtered" = 10 25
