#include <array>
#include <iostream>
#include <vector>

// Why we can't store pointer to vector in vector iterator to avoid
// invalidation?

// 1) Iterators must be valid after std::vector::swap:
// https://en.cppreference.com/w/cpp/container/vector/swap
// 2) Requires more dereferences

void TestVector() {
    std::cout << "TestVector\n";

    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{4, 5, 6, 7};
    auto it12 = v1.begin() + 1;

    std::cout << *it12;          // 2
    std::swap(v1, v2);           // O(1)
    std::cout << *it12 << '\n';  // 2
}

void TestArray() {
    std::cout << "TestArray\n";

    std::array<int, 3> a1{1, 2, 3};
    std::array<int, 3> a2{4, 5, 6};
    auto it12 = a1.begin() + 1;

    std::cout << *it12;          // 2
    std::swap(a1, a2);           // O(n)
    std::cout << *it12 << '\n';  // 5
}

int main() {
    TestVector();
    TestArray();
}
