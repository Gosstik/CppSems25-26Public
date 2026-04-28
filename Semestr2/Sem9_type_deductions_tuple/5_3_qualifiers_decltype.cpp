#include <iostream>
#include <vector>

template <typename T>
void Debug() = delete;

int main() {
    int x = 0;
    int& rx = x;
    const int cx = x;

    const decltype(x)& d1 = x;  // const and ref may be added
    decltype(cx) d2 = 1;        // save const
    decltype(x)& d3 = x;        // & is affected
    decltype(rx)&& d4 = x;      // & + && = &
    // !!! const has no effect (otherwise int& const)
    const decltype(rx) d5 = x;
    const decltype(&x) const d6 = &x;  // !!! not "const int* const"

    Debug<decltype(d1)>();  // const int&
    Debug<decltype(d2)>();  // const int
    Debug<decltype(d3)>();  // int&
    Debug<decltype(d4)>();  // int&
    Debug<decltype(d5)>();  // int&
    Debug<decltype(d6)>();  // int* const
}
