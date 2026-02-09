#include <iostream>

void Foo(int x) { std::cout << "Foo called with " << x << "\n"; }

template <typename... Args>
void ApplyToAll(Args... args) {
    // Foo(args)...;      // CE
    (Foo(args), ...);  // OK
}

int main() { ApplyToAll(1, 2, 3); }
