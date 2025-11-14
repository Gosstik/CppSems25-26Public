#include <iostream>
#include <string>

const int& Foo() { return 42; }

int main() {
    {
        // Lifetime expansion

        // When to remove? It is allocated dynamically
        const std::string& s = "aaa";

        // ...
        // f(s)

        // Answer: object is destroyed when (only) reference s comes out of
        // scope Compiler marks 's' as special link. It is 'lifetime expansion'
    }

    {
        const int& val = Foo();  // NO LIFETIME EXPANSION
        std::cout << val << '\n'; // UB
    }
}
