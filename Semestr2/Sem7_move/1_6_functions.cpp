#include <utility>

// What min number of versions to leave to compile a, b, c?     // ???
// What versions will cover all cases since c++11?              // ???
// What (max) versions to leave to compile a, (not b), (not c)? // ???
// What (max) versions to leave to compile b, c, (not a)?       // ???
// What versions to comment to compile b, (not c)?              // ???
// What versions to comment to compile c, (not b)?              // ???
// What if leave versions 1 and 3?                              // ???

// void Foo(const int&) {}  // 1
// void Foo(int&) {}        // 2
// void Foo(int&&) {}       // 3
// void Foo(int) {}         // 4
// void Foo(const int) {}   // 5

int main() {
    int x = 0;

    Foo(x);             // a
    Foo(std::move(x));  // b
    Foo(1);             // c
}
