// overloading lambdas
// union, std::variant, std::holds_alternative, std::get_if, std::visit

// tuple and its implementation

#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <map>

using namespace std;

template<typename ...> struct TD;

struct FunctionObjectInt
{
    auto operator() (int i) const
    { cout << "integer has been passed" << endl; }
};

auto lambda_int = [](int i) { cout << "integer has been passed" << endl; };

struct FunctionObjectFloat
{
    auto operator() (float f) const
    { cout << "float has been passed" << endl; }
};
auto lambda_float = [](float f) { cout << "float has been passed" << endl; };

struct FunctionObjectString
{
    auto operator() (const string& s) const
    { cout << "string has been passed" << endl; }
};
auto lambda_string = [](const string& s) { cout << "string has been passed" << endl; };

struct FunctionObjectIntFloatString : FunctionObjectInt, FunctionObjectFloat, FunctionObjectString
{
    using FunctionObjectInt::operator(), FunctionObjectFloat::operator(), FunctionObjectString::operator();
};

struct FunctionObject
{
    auto operator() (int i) const             { cout << "integer has been passed" << endl; }
    auto operator() (float f) const           { cout << "float has been passed" << endl; }
    auto operator() (const string& s) const   { cout << "string has been passed" << endl; }
};

template<typename ... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename ... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// implement variant

enum variant_ifs_type { INTEGER=0, FLOAT=1, STRING=2 };

struct variant_ifs {
    variant_ifs_type type;

//    union {
        int i;
        float f;
        string s;
//    };

    variant_ifs(int i) : type{INTEGER}, i{i} { }
    variant_ifs(float f) : type{FLOAT}, f{f} { }
    variant_ifs(string s) : type{STRING}, s{s} { }

    ~variant_ifs() { }

    template<typename T>
    void* get_if() const {
        if constexpr(std::is_same_v<T, int>) {
            if(type == INTEGER)
                return (void*)&i;
            return nullptr;
        }
        else if constexpr(std::is_same_v<T, float>) {
            if(type == FLOAT)
                return (void*)&f;
            return nullptr;
        }
        else if constexpr(std::is_same_v<T, string>) {
            if(type == STRING)
                return (void*)&s;
            return nullptr;
        }
        else
            return nullptr;
    }

    void operator=(int i) { type = INTEGER; this->i = i; }
    void operator=(float f) { type = FLOAT; this->f = f; }
    void operator=(string s) { type = STRING; this->s = s; }
};




int main()
{
    auto var = variant_ifs{100};
    var = 3.3f;
    var = string("hi there");

//    cout << var.f << endl;

    cout << var.get_if<string>() << endl;

    cout << *((string*)var.get_if<string>()) << endl;

    using VAR_IFS = std::variant<int, float, string>;

    auto var_ifs = VAR_IFS{100};

    cout << std::holds_alternative<float>(var_ifs) << endl;
    cout << *std::get_if<int>(&var_ifs) << endl;

    auto vector = std::vector<VAR_IFS>{
        10, 3.5f, "Hi there", 10, 10, 5.5f
    };

    auto m = std::map<string, VAR_IFS>{
        {"First Line", 10 },
        {"Blabla", "Hello" },
        {"...", 3.14f },
    };

    for(const auto& [key, value] : m) {
        cout << key << endl;
        // ...
    }

//    std::any


    auto L = overloaded{lambda_int, lambda_float, lambda_string};
//    auto L_all = []<typename T>(T&& whatever) {
//        using U = std::remove_cvref_t<T>;
//        if constexpr(std::is_same_v<U, int>) {

//        } else if constexpr(std::is_same_v<U, float>) {

//        } else if constexpr(std::is_same_v<U, string>) {

//        }
//    };

    auto var_ifs_2 = VAR_IFS{222.2f};

    std::visit(L, var_ifs_2);

    return 0;
}
