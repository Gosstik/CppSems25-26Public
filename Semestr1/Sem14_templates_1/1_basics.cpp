#include <iostream>

// What's wrong ? --- Min should accept const T&

template <typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T Min(T& a, T& b) {
    return a < b ? a : b;
}

template <typename T>
void Bar(T b = 1) {
    std::cout << 1 << '\n';
}

struct S {
    S() = default;
    S(int) {}
};

void Foo() { std::cout << 1 << '\n'; }

int main() {
    int a = 1;
    int b = 2;
    Swap(a, b);
    // Bar<int, void*>();
    S s;
    Bar<S>();
}
