#include <iostream>
#include <vector>

int main() {
    // Dangling pointer
    int a = 1;
    int* p = &a;
    {
        int b = 2;
        p = &b;
    }

    // std::cout << b << ' '; // CE
    std::cout << p << ' ';    // No UB, because no dereference
    std::cout << *p << '\n';  // UB, try O0 and O1 optimization

    int c = 3, d = 4, e = 5, f = 6;
    std::cout << &c << ' ' << &d << ' ' << &e << ' ' << &f << '\n';
    ++*p;  // UB
    std::cout << c << d << e << f << *p << '\n';

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::cout << v1.data() << ' ' << v1.data() + 1 << '\n';

    std::vector<int> v2 = {1, 2, 3, 4, 5};
    std::cout << v2.data() << ' ' << v2.data() + 1 << '\n';
}
