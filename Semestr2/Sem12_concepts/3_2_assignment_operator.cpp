#include <concepts>
#include <iostream>
#include <type_traits>

template <typename T>
struct AssignmentRequiresCopy {
    // ... other methods ...
    AssignmentRequiresCopy& operator=(const AssignmentRequiresCopy& other) {
        std::cout << "(1) Called operator=()\n";
        return *this;
    }

    // // How to write that T must be movable ???
    // template <typename T2 = T, typename =
    // std::enable_if_t<std::is_copy_constructible_v<T2>>>
    // AssignmentRequiresCopy& operator=(const AssignmentRequiresCopy& other) {
    //     std::cout << "(2) Called operator=()\n";
    //     return *this;
    // }

    // // Working with requires clause !!!
    // AssignmentRequiresCopy& operator=(const AssignmentRequiresCopy& other)
    // requires std::is_copy_constructible_v<T> {
    //     std::cout << "(3) Called operator=()\n";
    //     return *this;
    // }
};

int main() {
    AssignmentRequiresCopy<int> a1;
    AssignmentRequiresCopy<int> a2;
    std::cout << "BEFORE\n";
    a1 = a2;
    std::cout << "AFTER\n";
}
