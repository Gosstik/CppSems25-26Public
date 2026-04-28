#include <iostream>
#include <tuple>

int main() {
    {
        std::tuple t{1, 2.0, 'a'};
        auto& d1 = std::get<1>(t);
        auto& d2 = std::get<1>(std::move(t));   // CE
        auto&& d3 = std::get<1>(std::move(t));  // OK, value<1> not moved
        auto d4 = std::get<1>(std::move(t));    // OK, value<1> moved

        d1 = 3.14;
        std::cout << std::get<1>(t);  // 3.14
    }

    {
        // structured binding
        std::tuple t{1, 2.0, 'a'};

        auto [x, y, z] = t;  // copy
        auto& [x, y, z] = t;

        // map
        for (const auto& [key, value] : map) {
            // ...
        }
    }
}
