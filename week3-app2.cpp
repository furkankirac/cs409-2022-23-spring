#include <iostream>

// repeat-it algorithm

// function objects
// l-value, r-value, r-value binding reference

// move-ctor, move-assignment

using namespace std;


void real_job()
{
    cout << "Job done" << endl;
}

struct AnotherRealJob
{
    int i; // construction parameter

    AnotherRealJob(int i) : i(i) { }

    int operator()() const
    {
        return i*10;
    }
};

struct FancyRealJob
{
    string s; // construction parameter

    FancyRealJob(string s) : s(s) { }

    string operator()() const
    {
        return s;
    }
};


typedef void (*FunctionPtr)(); // cstyle
//using FunctionPtr = void (*)();

typedef int (*FunctionPtr2)(int); // cstyle

template<typename FuncObject>
void repeat_it(const FuncObject& func, int times) // l-value + r-value binding ref
{
    for(int i=0; i<times; i++) {
        cout << func() << endl;
    }
}

template<typename FuncObject>
void repeat_it(FuncObject& func, int times) // l-value binding ref
{
    for(int i=0; i<times; i++) {
        cout << func() << endl;
    }
}

int main(int argc, char* argv[])
{
//    repeat_it(&real_job, 10);

//    auto another_real_job = [i=100]() { return i * 10; };

    auto x = [i=100]() mutable {
        i++;
        return i * 10;
    };
    repeat_it(x, 3);

//    repeat_it(AnotherRealJob{100}, 3);
//    repeat_it(FancyRealJob{"Hi"}, 2);
}
