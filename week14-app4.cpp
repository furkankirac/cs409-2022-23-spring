// std::optional: c++17

#include <optional>
#include <iostream>

using namespace std;

// Bu fonksiyon, belirli bir koşulu karşılayan bir değer döndürebilir, ya da hiçbir şey döndürmeyebilir.
auto Compute(bool condition) -> optional<int> {
    if (condition) {
        return 42;  // Bir değer döndür
    } else {
        return nullopt;  // Hiçbir şey döndürme
    }
}


int main() {
    auto result = Compute(true);
    if (result.has_value()) {
        std::cout << "Value: " << result.value() << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    return 0;
}

