#include <iostream>

/// Compilation
// clang++ -std=c++23 lib_foo.cpp main_file.cpp && ./a.out
// clang++ -std=c++23 main_file.cpp && ./a.out

/// Show all symbols with their types (W = weak, w = weak undefined)
// readelf -s a.out
// readelf -sC a.out # with demangling
// readelf -sC main_file.o

// NOT STANDARD, GNU extension
__attribute__((weak)) void Foo() {
    std::cout << "weak\n";
}

int main() {
    Foo();
}
