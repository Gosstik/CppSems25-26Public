#include <cstdarg>
#include <iostream>

// https://en.cppreference.com/w/cpp/language/variadic_arguments.html
// https://en.cppreference.com/w/cpp/preprocessor/replace

#define NUMARGS(...) sizeof((int[]){__VA_ARGS__}) / sizeof(int)
#define PRINT(...) Print(NUMARGS(__VA_ARGS__), __VA_ARGS__)

int Print(int nargs, ...) {
    va_list ap;
    int cnt = 0;
    va_start(ap, nargs);

    for (int i = 0; i < nargs; ++i) {
        // !!! va_arg can be called only once
        if (i + 1 == nargs) {
            std::cout << va_arg(ap, int);
        } else {
            std::cout << va_arg(ap, int) << ", ";
        }
    }
    std::cout << '\n';

    va_end(ap);
    return cnt;
}

int main() {
    // int abc[] {1, 2, 3};
    // std::cout << sizeof(abc);

    std::cout << "PRINT(1, 2, 3): " << PRINT(1, 2, 3) << '\n';
    std::cout << "Print(3, 1, 2, 3): " << Print(3, 1, 2, 3) << '\n';
}
