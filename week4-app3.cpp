#include <iostream>
#include <vector>

// r-value binding reference
// move-ctor, move-assignment

using namespace std;

// legacy code that shows the dynamic heap allocation
struct VeryBigObject
{
    int* array = nullptr;
    VeryBigObject() {
        array = new int[100000000];
    }

    ~VeryBigObject() {
        delete[] array;
    }
};

// newer code that hides the new operator in the std::vector<int> object
struct VeryVeryBigObject
{
    std::vector<int> v;
    VeryVeryBigObject() : v(100000000) {}

    // copy ctor
    VeryVeryBigObject(const VeryVeryBigObject& other) : v{other.v} { }

    // move ctor (only r-value binding special ref)
    VeryVeryBigObject(VeryVeryBigObject&& other) : v{move(other.v)} { }

    void operator=(VeryVeryBigObject&& other)
    {
        v = std::move(other.v);
    }
};

template<typename T>
void SWAP(T& a, T& b)
{
    auto t = std::move(a); // a promise to the compiler that it's okay to steal the contents of "a"
    a = std::move(b); // a promise to the compiler that it's okay to steal the contents of "b"
    b = std::move(t); // a promise to the compiler that it's okay to steal the contents of "t"
}

int main(int argc, char* argv[])
{
    int a=10, b=20;
    SWAP(a, b);

    cout << "a=" << a << ", b=" << b << endl;
}
