#include <iostream>
#include <type_traits>

template <typename First, typename Second, typename... Types>
struct IsHomogeneous {
    static constexpr bool value =
        std::is_same_v<First, Second> && IsHomogeneous<Second, Types...>::value;
};

template <typename First, typename Second>
struct IsHomogeneous<First, Second> {
    static constexpr bool value = std::is_same_v<First, Second>;
};

template <typename... Args>
constexpr bool is_homogeneous_v = IsHomogeneous<Args...>::value;

void TestIsHomogeneous() {
    std::cout << is_homogeneous_v<int, int, double> << '\n';
}
