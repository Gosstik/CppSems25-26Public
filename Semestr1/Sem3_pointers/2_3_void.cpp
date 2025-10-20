#include <iostream>
#include <vector>

int main() {
    // void - incomplete type
    // any pointer can be casted to void*

    void a; // CE

    void* p;

    int val;
    int* pi = &val;
    p = &val; // OK

    std::vector<int> v;
    p = &v; // OK

    std::cout << sizeof(p);
    std::cout << *p << '\n'; // CE, unable to dereference void*
}
