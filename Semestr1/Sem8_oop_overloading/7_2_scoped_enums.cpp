#include <iostream>

enum /*class*/ E {
    White,  // 0
    Gray,   // 1
    Black,  // 2
};

enum Direction {
    Up,
    Right,
    Down,
    Left,
};

// scoped enum (struct and class are equivalent)
enum struct Alpha : int32_t {
    A,  // 0
    B = -2,
    C,  // -1
    D,  // 0
    E = 5,
    F = 5,
    G,  // 6
};

int main() {
    {
        // enum
        int e = White;
        if (White < Black) {
            std::cout << e << '\n';      // 0
            std::cout << Black << '\n';  // OK, 2
        }
    }

    {
        // scoped enum
        Alpha a = A;                         // CE, unqualified id
        int a = Alpha::A;                    // CE, implicit cast is disabled
        int b = static_cast<int>(Alpha::A);  // OK

        if (Alpha::B < Alpha::C) {
            std::cout << Alpha::C << '\n';  // CE
        }
    }
}
