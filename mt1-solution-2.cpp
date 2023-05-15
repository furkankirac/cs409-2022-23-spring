#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <variant>

using namespace std;

template<typename> struct RxConfig;

//struct X : std::variant<char, int, double> {
//    using std::variant<char, int, double>::variant;
//};

using X = std::variant<char, int, double>;

template<typename> struct RxConfig {
    static constexpr auto DOT = X{'.'};
    static constexpr auto CCbegin = X{'['};
    static constexpr auto CCend = X{']'};
    static constexpr auto DASH = X{'-'};
    static constexpr auto PARbegin = X{'('};
    static constexpr auto PARend = X{')'};
};

template<typename T>
concept MatchResult = requires (T t) {
    t.input;
    t.matched;
    t.parIdx;
};

template<typename T>
struct RxMatcher {
    using CharT = X;
    using CCVariant = variant<CharT, pair<CharT, CharT>>;
    using CFG = RxConfig<CharT>;

    struct Result {
        vector<X> input;
        bool matched = false;
        vector<pair<int, int>> parIdx;
    };

    vector<X> rx;
    Result result;

    RxMatcher(const char* rx_) : rx(string(rx_).size()) {
        auto sz = rx.size();
        for(int i=0; i<sz; i++)
            rx[i] = rx_[i];
    }

    RxMatcher(const T& rx_) : rx(rx_.size()) {
        auto sz = rx.size();
        for(int i=0; i<sz; i++)
            rx[i] = rx_[i];
    }

    auto parseCharacterClass(size_t start) const -> pair<set<CCVariant>, size_t> {
        auto char_class = set<CCVariant>{};
        auto i = size_t{start};

        while (i < rx.size() && rx[i] != CFG::CCend) {
            CharT c1 = rx[i++];
            if (i < rx.size() && rx[i] == CFG::DASH && i + 1 < rx.size()) {
                CharT c2 = rx[i + 1];
                i += 2;
                char_class.insert(pair{c1, c2});
            } else {
                char_class.insert(c1);
            }
        }

        return {char_class, i + 1};
    }

    Result findIn(const char * input) {
        auto sz = string(input).size();
        auto v = vector<X>(sz);
        for(int i=0; i<sz; i++)
            v[i] = input[i];
        return findIn(v);
    }

    template<typename U>
    Result findIn(const vector<U>& input_) {
        auto input = vector<X>(input_.size());
        for(int i=0; i< input_.size(); i++)
            input[i] = input_[i];
        return findIn(input);
    }

    Result findIn(const vector<X>& input) {
        result.parIdx.clear();
        auto i = 0;
        do {
            result.matched = findIn(input, i++, 0);
        } while(!result.matched && i < input.size() - 1);
        if(!result.matched) result.parIdx.clear();
        result.input = input;
        return result;
    }

    bool findIn(const vector<X>& input, size_t i, size_t j) {
        if (rx[j] == CFG::PARbegin) {
            result.parIdx.push_back({i, -1});
            return findIn(input, i, j + 1);
        } else if (rx[j] == CFG::PARend) {
            auto k = result.parIdx.size() - 1;
            while(result.parIdx[k].second != -1) k--;
            result.parIdx[k].second = i;
            return findIn(input, i, j + 1);
        } else if (j == rx.size()) { // if we're at the end of pattern's characters
            return true; //i == input.size(); // true if input is also finished else false
        } else if (rx[j] == CFG::CCbegin) {
            auto [char_class, next_j] = parseCharacterClass(j + 1);
            for(const CCVariant& cc : char_class) {
                const auto* ptr = get_if<CharT>(&cc);
                if(ptr) {
                    if(*ptr == input[i])
                        return findIn(input, i + 1, next_j);
                } else {
                    const auto [b, e] = get<pair<CharT, CharT>>(cc);
                    if(input[i] >= b && input[i] <= e)
                        return findIn(input, i + 1, next_j);
                }
            }
        } else if (i < input.size() && (rx[j] == CFG::DOT || input[i] == rx[j])) {
            return findIn(input, i + 1, j + 1);
        }

        return false;
    }
};

RxMatcher(const char*) -> RxMatcher<string>;

namespace std {
    vector(auto ...) -> vector<X>;
}

template<MatchResult ... MRs>
auto print(MRs&& ... mrs) {
    auto print_ = [=](auto&& mr) {
        auto str = string{};
        for(auto&& item : mr.input)
            str += get<char>(item);

        cout << "Input: \"" << str << "\"" << endl << "Matched: " << mr.matched << "  ";

        for(auto&& [b, e] : mr.parIdx)
            cout << "(" << b << "," << e << ")=" << str.substr(b, e-b) << " ";

        cout << endl;
    };

    (print_(mrs), ...);
}

int main() {
    cout << boolalpha;
    {
        cout << "STRING matcher" << endl;
        auto matcher = RxMatcher("h((.[a-z])(lo))");
        print(
            matcher.findIn("hello "),
            matcher.findIn("hallo"),
            matcher.findIn("_hEblo!"),
            matcher.findIn("heako")
            );
    }
    cout << endl;

    {
        cout << "INT matcher" << endl;
        using CFG = RxConfig<int>;
        auto matcher1 = RxMatcher(vector{1, CFG::DOT, CFG::CCbegin, 10, 20, CFG::CCend, 4});
        cout << matcher1.findIn(vector{1, 2, 20, 4}).matched << endl;
        cout << matcher1.findIn(vector{1, 2, 15, 4}).matched << endl;

        auto matcher2 = RxMatcher(vector{1, CFG::DOT, CFG::CCbegin, 10, CFG::DASH, 20, CFG::CCend, 4});
        cout << matcher2.findIn(vector{1, 2, 15, 4}).matched << endl;
    }
    cout << endl;

    {
        cout << "DOUBLE matcher" << endl;
        using CFG = RxConfig<double>;
        auto matcher1 = RxMatcher(vector{1.1, CFG::DOT, CFG::CCbegin, 10.0, CFG::DASH, 20.0, CFG::CCend, 4.0});
        cout << matcher1.findIn(vector{1.1, 2.5, 15.5, 4.0}).matched << endl;
    }
    return 0;
}
