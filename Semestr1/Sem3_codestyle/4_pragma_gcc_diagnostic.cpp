//! These pragmas override ANY command-line options
// Pragma diagnostic expect 'error', 'warning', 'ignored', 'fatal', 'push', or
// 'pop'

// clang++ -std=c++20 -Wall -Wextra -pedantic -Werror -g -fsanitize=address,undefined main.cpp
// Add -Wno-unused-value

int main() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

    int x = 0;  // no warning or error

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"

    x + 2;  // no warning or error

#pragma GCC diagnostic pop

    x + 4;  // warning

#pragma GCC diagnostic pop

    int y = 0;  // warning

// #pragma GCC diagnostic pop  // 3rd pop, try uncomment and compile
}
