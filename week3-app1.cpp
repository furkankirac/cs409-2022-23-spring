#include <iostream>

// operator overloading
// function-call operator
// function objects
// function pointers

// getter, setter
// returning a reference
// l-value, r-value, r-value binding reference
// repeat-it algorithm

// move-ctor, move-assignment

using namespace std;

struct Foo
{
private:
    int a = 10;
    float f = 12.3f;

public:
    int getInt() { return a; }
    int& getIntRef() { return a; }
    int* getIntPtr() { return &a; }
    Foo()// : a{20}, f{12.3f}
    {    }
    Foo(int a) : a{a}, f{float(a)}
    {    }
    Foo(int a, float f) : a{a}, f{f}
    {    }
    // copy ctor
    Foo(const Foo& other) : a{other.a}, f{other.f}
    {    }

    void operator() () {
        cout << "I am Foo instance, and I am being called as if I am a function." << endl;
    }

    // left is binding only to l-values,
    // right can bind to both l-value and r-value
    void operator=(const Foo& right) // copy assignment
    {
        a = right.a;
        f = right.f;
    }

    void operator=(int k) // copy assignment
    {
        a = k;
        f = k;
    }


    void print()
    {
        cout << "I am foo with values (a, f)=" << a << "," << f << endl;
    }
};

//int* getIntPtr(Foo& foo) { return &foo.a; }

//int operator+(string a, string b) {
//    return a.size() + b.size();
//}

void nothing()
{
}

struct Bar {
    int a;
    float f;
    double d;
    string s;


    void operator()(char c)
    {

    }
};

void func(int a, float f, double d, string s, char c)
{

}




int main(int argc, char* argv[])
{
    4 + 5;     // in-fix notation

    cout << sizeof(Foo) << endl;

    auto foo = Foo{}; // default ctor
    foo.print();

//    auto foo2 = Foo(foo); // copy ctor
    auto foo2 = foo; // copy ctor
    foo2 = Foo{100, 3.14f}; // copy assignment
    foo2 = 200; // copy assignment
    foo2.print();
    auto foo3 = Foo{300};

    cout << "foo3.getInt() is " << foo3.getInt() << endl;
//    foo3.getInt() = 400; // left hand side is now an r-value
    foo3.getIntRef() = 400; // left hand side is now an r-value
    cout << "foo3.getInt() is " << foo3.getInt() << endl;

    *(foo3.getIntPtr()) = 400; // left hand side is now an r-value

    foo3();
//    foo3.operator()();

//    foo = foo2 = foo3; // chained assignment operator works from right to left

//    operator=(foo2, Foo{100, 3.14f});

    nothing();


//    operator+(4, 5);
//    add(4, 5);
    cout << (string("hi") + string("there")) << endl;
}
