#include <iostream>

// https://man.archlinux.org/man/core/gcc/__gnu_cxx::recursive_init_error.3.en
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf
// [stmt.dcl], If control re-enters the declaration recursively while the variable is being initialized, the behavior is undefined.

int x = 1;

int Foo(int n) {
    if (n == 0) {
        return 0;
    }
    static int x = Foo(n - 1) + ::x;
    return x;
}

int main() {
    std::cout << Foo(3) << " " << Foo(3) << std::endl; // !!! UB
}
