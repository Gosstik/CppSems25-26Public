#include <cstddef>  // std::ptrdiff_t
#include <iostream>

int main() {
    // Operations
    int x = 10;
    int y = 20;
    int* px = &x;
    int* py = &y;

    // arithmetic
    px = px + 1;
    px += 1;
    ++px;
    px -= 3;

    bool not_equal = px != py;  // OK
    bool is_less = px < py;     // Unspecified

    std::ptrdiff_t pz = px - py;  // UB
    int* pp = px + py;       // CE

    &x = 1;               // CE, &x is rvalue
    int* px1 = &(x + 1);  // CE, (x + 1) is rvalue
}
