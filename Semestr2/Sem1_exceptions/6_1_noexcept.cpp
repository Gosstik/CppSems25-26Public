#include <iostream>

// noexcept keyword appeared in C++11

// noexcept operator
// noexcept specifier

// operator checks in compile time that expression IS DECLARED as not throw
// operator accepts EXPRESSION, not a function

// noexcept(expression) works as follows:
// 1) checks each subexpression of expression
// 2) if subexpression is function - check noexcept specifier
// 3) if subexpression is operator - only 4 operators may throw

void Foo() { throw 1; }

void Bar() noexcept { throw 2; }

int main() {
    std::cout << noexcept(Foo) << '\n';    // 1, just pointer
    std::cout << noexcept(Foo()) << '\n';  // 0, function call

    if constexpr (noexcept(1 - 1)) {
        std::cout << "1 - 1 is noexcept\n";
    }

    try {
        // Foo();
        // not caught exception in noexcept function calls std::terminate()
        Bar();
    } catch (...) {
        std::cout << "caught!\n";
    }
}
