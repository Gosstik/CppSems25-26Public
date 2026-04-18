#include <iostream>
#include <utility>

// Source: https://cppquiz.org/quiz/question/116

// Task: According to the C++23 standard, what is the output of this program?

int y(int&) { return 1; }
int y(int&&) { return 2; }

template <class T>
int f(T&& x) {
    return y(x);
}
template <class T>
int g(T&& x) {
    return y(std::move(x));
}
template <class T>
int h(T&& x) {
    return y(std::forward<T>(x));
}

int main() {
    int i = 10;
    std::cout << f(i) << f(20);
    std::cout << g(i) << g(20);
    std::cout << h(i) << h(20);
    return 0;
}
