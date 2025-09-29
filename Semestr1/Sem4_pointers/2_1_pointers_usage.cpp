#include <iostream>

int main() {
    int x = 10;
    int y = 20;
    std::cout << &x << '\n';

    int* p = &x;
    std::cout << *p << '\n';                 // dereference
    std::cout << *&p << ' ' << &*p << '\n';  // OK

    int *a1, a2;             // NOTE: ai is int*, a2 is int
    int *p1 = &x, *p2 = &y;  // both p1 and p2 are int*

    std::cout << p1 << ' ' << p2 << '\n';

    int* tptr = (int*)0x00ff;
    std::cout << *tptr << '\n';  // UB
}
