#include <iostream>
#include <tuple>

template <typename... Ts>
struct X {
    // explicit X(Ts&... values): values(std::make_tuple(values...)) {}
    explicit X(const Ts&... values) : values(std::tie(values...)) {}  // fix

    std::tuple<const Ts&...> values;
};

int main() {
    int i = 42;
    auto s = std::string("universe");

    auto x = X<int, std::string>(i, s);

    std::cout << "i = " << std::get<0>(x.values) << '\n';
    std::cout << "s = " << std::get<1>(x.values) << '\n';
}
