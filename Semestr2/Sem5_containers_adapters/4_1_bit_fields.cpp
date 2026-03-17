#include <bit>

// Bit Fields
// https://en.cppreference.com/w/cpp/language/bit_field

// See examples on cppreference.

// Convenient for parsing network packets (with reinterpret_cast).

// !!! NOTE: std::bit_cast
// ??? What are the advantages of std::bit_cast over reinterpret_cast?

int main() {
    float f = 3.14f;

    // UB (aliasing violation)
    int rci = *reinterpret_cast<int*>(&f);

    // OK
    int bci = *std::bit_cast<int*>(&f);
}
